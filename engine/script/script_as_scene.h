//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Scene
//
//=============================================================================
#ifndef __UAC__SCRIPT_AS_SCENE_H
#define __UAC__SCRIPT_AS_SCENE_H

#ifdef USE_ASLIB

#include "angelscript.h"


namespace UAC
{
namespace Engine
{


void RegisterScene(asIScriptEngine* engine);


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_AS_SCENE_H
