//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  Irrlicht Interface for ISceneManager
//
//=============================================================================
#ifndef __UAC__SCENE_MANAGER_IRR_H
#define __UAC__SCENE_MANAGER_IRR_H

#ifdef USE_IRRLIB

#include "scene/node_irr.h"
#include "scene/scene_manager.h"


namespace UAC
{
namespace Engine
{


class SceneManagerIrr : public Common::ISceneManager
{
public:
	SceneManagerIrr();
	virtual ~SceneManagerIrr();
	

	virtual void Init(Common::IDevice* device);

	virtual irr::scene::ISceneManager* GetSceneManagerIrr() const { return _smgr; }

	//! Create a node and add it to the manager.
	virtual Common::INodeScene* CreateSceneNode(Common::INodeScene* parent, const std::string& scriptname);
	virtual Common::INodeCamera* CreateCameraNode(Common::INodeScene* parent, const std::string& scriptname);
	virtual Common::INodeLight* CreateLightNode(Common::INodeScene* parent, Common::LIGHT_TYPE type, const std::string& scriptname);
	virtual Common::INodeMesh* CreateMeshNode(Common::INodeScene* parent, const std::string& scriptname, const std::string& filename);


	virtual void Update() {} //TEMP

	virtual void Render();
	

	//! Load scenes from file
	virtual bool LoadScenesFromFile();


protected:
	irr::scene::ISceneManager* _smgr;
};

} // namespace Engine
} // namespace UAC

#endif // USE_IRRLIB

#endif  // __UAC__SCENE_MANAGER_IRR_H
