//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  Scene manager interface
//	The Scene Manager manages a collection of scenes. It also manages the update
//	and rendering of those scenes and provides a mechanism to easily switch between
//	them.
//	The scene manager uses the concept of the "current scene" where only one scene 
//	can be active at any given time.
//
//=============================================================================
#ifndef __UAC__SCENE_MANAGER_H
#define __UAC__SCENE_MANAGER_H

#include "scene/node_scene.h"
#include "scene/node_camera.h"
#include "scene/node_light.h"
#include "scene/node_mesh.h"
#include "device/device.h"



namespace UAC
{
namespace Common
{


class ISceneManager
{
public:
	ISceneManager();
	virtual ~ISceneManager();

	//! Initialize the scene manager.
	virtual void Init(IDevice* device);

	
	//! Adds a scene to the manager.
	virtual void Add(INodeScene* scene);

	//! Removes the given scene from the scene manager.
	virtual void Remove(INodeScene* scene);
	
	//! Removes all children of the scene manager.
	virtual void RemoveAll();
	
	//! Create a node and add it to the manager.
	virtual Common::INodeScene* CreateSceneNode(INode* parent, const std::string& scriptname) = 0;
	virtual Common::INodeCamera* CreateCameraNode(INode* parent, const std::string& scriptname) = 0;
	virtual Common::INodeLight* CreateLightNode(INode* parent, LIGHT_TYPE type, const std::string& scriptname) = 0;
	virtual Common::INodeMesh* CreateMeshNode(INode* parent, const std::string& filename, const std::string& scriptname) = 0;

	//! Searches for the named scene.
	//INodeScene* Find(const char* name);


	//! Renders the active scene.
	virtual void Render() = 0;


	//! Load scenes from file
	virtual bool LoadScenesFromFile();

	//TEMP - temporanea per testare il caricamento da script
	INodeScene* GetRoot() { return _scenes[0]; }


protected:
	INodeScene* _current;				// Currently active scene
	INodeScene* _next;					// Next scene (scene that is being switched to)
	std::vector<INodeScene*> _scenes;	// Scenes collection

	IDevice* _device;
	IGFXDriver* _gfxdriver;

	//TEMP
	int _node_depth;
	bool _read_node(pugi::xml_node& xmlnode, INode* parent = 0);



	/*
	INodeScene* GetCurrent() { return _current; }

	/**
	* @fn    void SceneManager::SwitchTo(Scene* scene);
	*
	* @brief Switch to a new scene.
	*
	* @param scene   Thew new scene.
	*
	void SwitchTo(INodeScene* scene);

	/**
	* @fn    void SceneManager::Update(float deltaTime = 0.0f);
	*
	* @brief Updates all scenes managed by the manager
	*
	* @param deltaTime   Number of seconds that has passed since Update() was last called.
	*
	void Update(float deltaTime = 0.0f);

	
	/**
	* @fn    bool SceneManager::Run();
	*
	* @brief Runs the device.
	*
	* @return    false if device wants to be deleted.
	*
	bool Run();
	
	/**
	* @fn    bool SceneManager::isWindowActive();
	*
	* @brief Returns if the window is active.
	*
	* @return    true if the window is active.
	*
	bool isWindowActive();

	// Internal
	static void OnSwitchComplete(CTween* pTween);
	void FinishSwitch();
	*/
};

} // namespace Common
} // namespace UAC

#endif  // __UAC__SCENE_MANAGER_H
