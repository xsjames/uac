//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Scripting System creation helper
//
//=============================================================================

#include "script/script_helper.h"
#ifdef USE_ASLIB
#include "script/script_as.h"
#endif


namespace UAC
{

using namespace Common;

namespace Engine
{


bool CreateScriptingSystem(Common::IScript** scriptSys)
{
#ifdef USE_ASLIB
	*scriptSys = new ScriptAS();
	return *scriptSys ? true : false;
#endif

	return false;
}


void DestroyScriptingSystem(Common::IScript** scriptSys)
{
	if(*scriptSys)
	{
		delete *scriptSys;
		*scriptSys = 0;
	}
}


} // namespace Engine
} // namespace UAC
