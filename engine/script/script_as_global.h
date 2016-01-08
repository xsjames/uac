//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Global functions
//
//=============================================================================
#ifndef __UAC__SCRIPT_AS_GLOBAL_H
#define __UAC__SCRIPT_AS_GLOBAL_H

#ifdef USE_ASLIB

#include "angelscript.h"


namespace UAC
{
namespace Engine
{


	void RegisterGlobalFunctions(asIScriptEngine* engine);


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_AS_GLOBAL_H
