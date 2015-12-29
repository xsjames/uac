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

#include "angelscript.h"
#include "script/script.h"


namespace UAC
{
namespace Engine
{

	
// enumerations -------------------------------------------------------------
enum ScriptFunctionIDs
{
	Function_InitApp = 0
};

const unsigned int max_script_functions = 1;


class ScriptAS : public Common::IScript
{
public:
	ScriptAS()
		: Common::IScript()
	{}

	virtual ~ScriptAS() { Shutdown(); }

	virtual const char* GetName() { return "Angel Script"; }
	virtual const char* GetID() { return "AS"; }
	

	virtual bool Init();
	virtual void Shutdown();


	virtual void RegisterGameInterface();
	virtual int LoadScript();

	void ExecuteFunction(ScriptFunctionIDs func_id);

//protected:
	asIScriptEngine* _engine;

	asIScriptContext* _ctx;
	asIScriptFunction* _script_functions[max_script_functions];
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_H
