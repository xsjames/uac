//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  Irrlicht Interface for ISceneManager
//
//=============================================================================

#ifdef USE_IRRLIB
#include "scene/scene_manager_irr.h"
#include "scene/node_scene_irr.h"
#include "scene/node_camera_irr.h"
#include "scene/node_light_irr.h"
#include "scene/node_mesh_irr.h"
#include "device/device_irr.h"
#include "debug/out.h"


using namespace irr;


namespace UAC
{

using namespace Common;

namespace Engine
{


SceneManagerIrr::SceneManagerIrr()
	: ISceneManager()
	, _smgr(0)
{
}

SceneManagerIrr::~SceneManagerIrr()
{
}


void SceneManagerIrr::Init(IDevice* device)
{
	ISceneManager::Init(device);

	if(strcmp(_device->GetID(), "IRR") != 0)
	{
		LOG(FATAL)("Only IRR SceneManager is supported!");
		return;
	}

	_smgr = ((DeviceIrr*)_device)->GetDeviceIrr()->getSceneManager();
}


bool SceneManagerIrr::LoadScenesFromFile()
{
	if(!ISceneManager::LoadScenesFromFile())
		return false;

	return true;
}


INodeScene* SceneManagerIrr::CreateSceneNode(INodeScene* parent, const std::string& scriptname)
{
	NodeSceneIrr* node = new NodeSceneIrr(parent, this, scriptname);
	if(!node)
	{
		LOG(FATAL)("Unable to add scene node!");
		return 0;
	}
	
	scene::ISceneNode* parent_irr = 0;
	if(parent)
		parent_irr = ((NodeSceneIrr*)parent)->GetNodeIrr();

	scene::ISceneNode* node_irr = _smgr->addEmptySceneNode(parent_irr);
	if(!node_irr)
	{
		LOG(FATAL)("Unable to add scene node (IRR)!");
		delete node;
		return 0;
	}
	//
	node->SetNodeIrr(node_irr);
	
	// sets ambient light in irr engine
	node->SetAmbientLight(node->GetAmbientLight());

	return node;
}

INodeCamera* SceneManagerIrr::CreateCameraNode(INodeScene* parent, const std::string& scriptname)
{
	NodeCameraIrr* node = new NodeCameraIrr(parent, this, scriptname);
	if(!node)
	{
		LOG(FATAL)("Unable to add camera node!");
		return 0;
	}
	
	scene::ISceneNode* parent_irr = 0;
	if(parent)
	{
		parent_irr = ((NodeSceneIrr*)parent)->GetNodeIrr();

		parent->SetActiveCamera(node);
	}

	scene::ICameraSceneNode* node_irr = _smgr->addCameraSceneNode(parent_irr);
	if(!node_irr)
	{
		LOG(FATAL)("Unable to add camera node (IRR)!");
		delete node;
		return 0;
	}
	//
	node->SetNodeIrr(node_irr);

	// workaround: Irrlicht seem to set the last camera added as active
	_current->SetActiveCamera(_current->GetActiveCamera());


	//TEMP provvisorio
	node_irr->bindTargetAndRotation(true);
	
	scene::ISceneNode* parent_node = _smgr->addEmptySceneNode(parent_irr/*, IDFlag_IsNotPickable*/);

	vector3f _position(-15.000000, 30.000000, -110.000000);
	vector3f _direction(10.000000, 17.000000, 0.000000);

	parent_node->setPosition(core::vector3df(_position.X, _position.Y, _position.Z));
	parent_node->setRotation(core::vector3df(_direction.X, _direction.Y, _direction.Z));

	// get transformation matrix of node
	core::matrix4 m;
	m.setRotationDegrees(parent_node->getRotation());

	// transform forward vector of camera
	core::vector3df frv = core::vector3df( 0.0f, 0.0f, 1.0f );
	m.transformVect( frv );

	// transform upvector of camera
	core::vector3df upv = core::vector3df( 0.0f, 1.0f, 0.0f );
	m.transformVect( upv );

	// transform camera offset
	/* //TEMP - per aggiungere offset alla telecamera
	m.transformVect( offset );
	irr_camera->setPosition( node->getPosition() + offset );
	*/

	// set camera
	node_irr->setPosition( parent_node->getPosition() );
	node_irr->setUpVector( upv ); //set up vector of camera
	node_irr->setTarget( parent_node->getPosition() + frv ); //set target of camera (look at point)

	return node;
}

INodeLight* SceneManagerIrr::CreateLightNode(INodeScene* parent, LIGHT_TYPE type, const std::string& scriptname)
{
	NodeLightIrr* node = new NodeLightIrr(parent, this, type, scriptname);
	if(!node)
	{
		LOG(FATAL)("Unable to add light node!");
		return 0;
	}

	scene::ISceneNode* parent_irr = 0;
	if(parent)
		parent_irr = ((NodeSceneIrr*)parent)->GetNodeIrr();

	float _distance = 500;
	vector3f _direction(45.000000, 70.000000, 0.000000);
	float _radius = 2000;

	if(type == LT_DIRECTIONAL)
	{
		if(_distance <= 0.f)
			_distance = 1000.f;

		// create rotation matrix
		core::matrix4 m;
		core::vector3df dir(_direction.X, _direction.Y, _direction.Z);
		m.setRotationDegrees(dir);
		// transform forward vector
		core::vector3df frv = core::vector3df(0.0f, 0.0f, -_distance);
		m.transformVect(frv);

		scene::ILightSceneNode* node_irr = _smgr->addLightSceneNode(parent_irr, frv, video::SColorf(1.0f, 1.0f, 1.0f), _radius/*, IDFlag_IsNotPickable*/);
		if(!node_irr)
		{
			LOG(FATAL)("Unable to add light node (IRR)!");
			delete node;
			return false;
		}
		//
		node->SetNodeIrr(node_irr);
		//
		node_irr->getLightData().Type = video::ELT_DIRECTIONAL;
		node_irr->setRotation(dir);
	}
	else if(type == LT_SPOT)
	{
		return 0;
	}
	else // LT_POINT
	{
		return 0;
	}

	return node;
}

INodeMesh* SceneManagerIrr::CreateMeshNode(INodeScene* parent, const std::string& filename, const std::string& scriptname)
{
	NodeMeshIrr* node = new NodeMeshIrr(parent, this, filename, scriptname);
	if(!node)
	{
		LOG(FATAL)("Unable to add mesh node!");
		return 0;
	}

	scene::IAnimatedMesh* mesh = _smgr->getMesh(filename.c_str());
	if(!mesh)
	{
		LOG(FATAL)("Unable to load mesh file: %s", filename.c_str());
		delete node;
		return 0;
	}

	scene::ISceneNode* parent_irr = 0;
	if(parent)
		parent_irr = ((NodeSceneIrr*)parent)->GetNodeIrr();

	scene::IAnimatedMeshSceneNode* node_irr = _smgr->addAnimatedMeshSceneNode(mesh, parent_irr/*, IDFlag_IsPickable*/);
	if(!node_irr)
	{
		LOG(FATAL)("Unable to add mesh node (IRR)!");
		delete node;
		return 0;
	}
	//
	node->SetNodeIrr(node_irr);

/*
	_node_irr->setPosition(core::vector3df(_position.X, _position.Y, _position.Z));
	_node_irr->setRotation(core::vector3df(_rotation.X, _rotation.Y, _rotation.Z));

	_node_irr->setScale(core::vector3df(_scale.X, _scale.Y, _scale.Z));
	// need to scale the mesh properly
	_node_irr->setMaterialFlag( video::EMF_NORMALIZE_NORMALS, true );
*/

	return node;
}

//TEMP
s32 lastFPS = -1;
void SceneManagerIrr::Render()
{
	video::IVideoDriver* drv = ((DeviceIrr*)_device)->GetDeviceIrr()->getVideoDriver();
	const s32 fps = drv->getFPS();
	if(lastFPS != fps)
	{
		core::stringw str = L"UAC Engine - Hello World! [";
		str += drv->getName();
		str += "] FPS:";
		str += fps;

		((DeviceIrr*)_device)->GetDeviceIrr()->setWindowCaption(str.c_str());
		lastFPS = fps;
	}

	_gfxdriver->Render();
}


} // namespace Engine
} // namespace UAC

#endif // USE_IRRLIB
