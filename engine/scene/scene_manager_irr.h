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
	virtual Common::INodeScene* CreateSceneNode(Common::INode* parent, const std::string& scriptname);
	virtual Common::INodeCamera* CreateCameraNode(Common::INode* parent, const std::string& scriptname);
	virtual Common::INodeLight* CreateLightNode(Common::INode* parent, const std::string& scriptname);
	virtual Common::INodeMesh* CreateMeshNode(Common::INode* parent, const std::string& scriptname, const std::string& filename);

	//TEMP
	//! Renders the active scene.
	virtual void Render() { _gfxdriver->Render(); }
	

	//! Load scenes from file
	virtual bool LoadScenesFromFile();


protected:
	irr::scene::ISceneManager* _smgr;
};

} // namespace Engine
} // namespace UAC

#endif // USE_IRRLIB

#endif  // __UAC__SCENE_MANAGER_IRR_H
