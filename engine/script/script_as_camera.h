//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Camera
//
//=============================================================================
#ifndef __UAC__SCRIPT_AS_CAMERA_H
#define __UAC__SCRIPT_AS_CAMERA_H

#ifdef USE_ASLIB

#include "angelscript.h"


namespace UAC
{
namespace Engine
{


void RegisterCamera(asIScriptEngine* engine);


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_AS_CAMERA_H
