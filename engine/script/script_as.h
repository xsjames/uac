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


class ScriptAS : public Common::IScript
{
public:
	ScriptAS()
		: Common::IScript()
		, _engine(0), _ctx(0)
	{
		for (int i = 0; i < Common::ScriptFunctionsMax; ++i)
			_script_functions[i] = 0;
	}

	virtual ~ScriptAS() { Shutdown(); }

	virtual const char* GetName() { return "Angel Script"; }
	virtual const char* GetID() { return "AS"; }
	

	virtual bool Init();
	virtual void Shutdown();


	virtual void RegisterGameInterface();
	virtual int LoadScript();

	virtual void ExecuteFunction(Common::ScriptFunctionIDs func_id);

protected:
	asIScriptEngine* _engine;

	asIScriptContext* _ctx;
	asIScriptFunction* _script_functions[Common::ScriptFunctionsMax];
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_H
