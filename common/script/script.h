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


namespace UAC
{
namespace Common
{


enum ScriptFunctionIDs
{
	Function_GameStart = 0,
	Function_RepeatedlyExecute = 1,
	ScriptFunctionsMax
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

	virtual void ExecuteFunction(ScriptFunctionIDs func_id) = 0;
};


}   // namespace Common
}   // namespace UAC

#endif // __UAC__SCRIPT_H
