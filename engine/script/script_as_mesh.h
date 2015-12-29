//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Mesh
//
//=============================================================================
#ifndef __UAC__SCRIPT_AS_MESH_H
#define __UAC__SCRIPT_AS_MESH_H

#ifdef USE_ASLIB

#include "angelscript.h"


namespace UAC
{
namespace Engine
{


void RegisterMesh(asIScriptEngine* engine);


}   // namespace Engine
}   // namespace UAC

#endif // USE_ASLIB

#endif // __UAC__SCRIPT_AS_MESH_H
