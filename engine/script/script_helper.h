//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Scripting System creation helper
//
//=============================================================================

#ifndef __UAC__SCRIPT_HELPER_H
#define __UAC__SCRIPT_HELPER_H

#include "script/script.h"


namespace UAC
{
namespace Engine
{

bool CreateScriptingSystem(Common::IScript** scriptSys);
void DestroyScriptingSystem(Common::IScript** scriptSys);

} // namespace Engine
} // namespace UAC


#endif // __UAC__SCRIPT_HELPER_H
