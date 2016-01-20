//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Irrlicht Interface for UAC INodeScene
//
//=============================================================================

#ifdef USE_IRRLIB
#include "scene/node_scene_irr.h"
#include "scene/node_camera_irr.h"
#include "scene/scene_manager_irr.h"

using namespace irr;


namespace UAC
{

using namespace Common;

namespace Engine
{


void NodeSceneIrr::SetActive(bool active)
{
	INodeScene::SetActive(active);

	if(IsActive() && IsVisible())
	{
		_node_irr->setVisible(true);

		_setActiveCameraIrr();
		_setAMbientLightIrr();
	}
	else
	{
		_node_irr->setVisible(false);
	}
}


void NodeSceneIrr::SetActiveCamera(INodeCamera* camera)
{
	_activeCamera = camera;

	if(IsActive())
		_setActiveCameraIrr();
}


void NodeSceneIrr::_setActiveCameraIrr()
{
	if(_activeCamera)
	{
		NodeCameraIrr* camera_irr = (NodeCameraIrr*)_activeCamera;
		GetNodeIrr()->getSceneManager()->setActiveCamera((scene::ICameraSceneNode*)camera_irr->GetNodeIrr());
	}
}


void NodeSceneIrr::_setAMbientLightIrr()
{
	GetNodeIrr()->getSceneManager()->setAmbientLight(irr::video::SColor(255, _ambientLight.r, _ambientLight.g, _ambientLight.b));
}


} // namespace Engine
} // namespace UAC

#endif // USE_IRRLIB
