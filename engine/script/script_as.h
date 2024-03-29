//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface
//
//=============================================================================
#ifndef __UAC__SCRIPT_AS_H
#define __UAC__SCRIPT_AS_H

#ifdef USE_ASLIB

#include <vector>
#include "angelscript.h"
#include "script/script.h"


namespace UAC
{
namespace Engine
{

struct SceneController
{
	Common::INodeScene* scene;
	asIScriptObject* scriptObj;
	asIScriptFunction* functions[Common::SceneFunction_Max];

	SceneController()
	{
		scene = 0;
		scriptObj = 0;

		for(int i = 0; i < Common::SceneFunction_Max; ++i)
			functions[i] = 0;
	}
};


class ScriptAS : public Common::IScript
{
public:
	ScriptAS()
		: Common::IScript()
		, _engine(0), _ctx(0), _active_scene(0), _active_scene_ctrl(0)
	{
		for (int i = 0; i < Common::GlobalFunction_Max; ++i)
			_global_functions[i] = 0;
	}

	virtual ~ScriptAS() { Shutdown(); }

	virtual const char* GetName() { return "Angel Script"; }
	virtual const char* GetID() { return "AS"; }
	

	virtual bool Init();
	virtual void Shutdown();


	virtual void RegisterGameInterface();
	virtual int LoadScript();


	virtual void Execute_GlobalFunction(Common::ScriptGlobalFunctionIDs func_id);
	// Execute the active scene functions
	virtual void SetActiveScene(Common::INodeScene* scene);
	virtual void Execute_SceneFunction(Common::ScriptSceneFunctionIDs func_id);
	//
	virtual void ReleaseScriptObjects() { ReleaseSceneControllers(); };


	virtual void AddSceneController(SceneController* ctrl);
	virtual SceneController* FindSceneController(Common::INodeScene* scene);
	virtual void ReleaseSceneControllers();


protected:
	asIScriptEngine* _engine;

	asIScriptContext* _ctx;
	asIScriptFunction* _global_functions[Common::GlobalFunction_Max];

	Common::INodeScene* _active_scene;
	SceneController* _active_scene_ctrl;
	std::vector<SceneController*> _scenes_controllers;	// Scenes controllers
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_H
