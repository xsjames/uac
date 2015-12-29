//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Light
//
//=============================================================================
#ifndef __UAC__SCRIPT_AS_LIGHT_H
#define __UAC__SCRIPT_AS_LIGHT_H

#ifdef USE_ASLIB

#include "angelscript.h"


namespace UAC
{
namespace Engine
{


void RegisterLight(asIScriptEngine* engine);


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_AS_LIGHT_H
