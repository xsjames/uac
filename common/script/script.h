//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface
//
//=============================================================================
#ifndef __UAC__SCRIPT_H
#define __UAC__SCRIPT_H

#include "scene/node_scene.h"


namespace UAC
{
namespace Common
{


enum ScriptGlobalFunctionIDs
{
	Global_GameStart = 0,
	Global_RepeatedlyExecute = 1,
	GlobalFunction_Max
};


enum ScriptSceneFunctionIDs
{
	Scene_RepeatedlyExecute = 0,
	SceneFunction_Max
};


class IScript
{
public:
	IScript() {}

	virtual ~IScript() {}

	virtual const char* GetName() = 0;
	virtual const char* GetID() = 0;


	virtual bool Init() = 0;
	virtual void Shutdown() = 0;


	virtual void RegisterGameInterface() = 0;
	virtual int LoadScript() = 0;


	virtual void Execute_GlobalFunction(ScriptGlobalFunctionIDs func_id) = 0;

	// Execute the active scene functions
	virtual void SetActiveScene(INodeScene* scene) = 0;
	virtual void Execute_SceneFunction(ScriptSceneFunctionIDs func_id) = 0;
};


}   // namespace Common
}   // namespace UAC

#endif // __UAC__SCRIPT_H
