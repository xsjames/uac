//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - GLobal functions
//
//=============================================================================

#ifdef USE_ASLIB

#include <assert.h>  // assert()
#include <string>
#include <iostream>
#include <windows.h> // timeGetTime()
#include "script/script_as_global.h"
#include "scene/scene_manager.h"
#include "debug/out.h"


extern UAC::Common::ISceneManager* g_pSceneManager;


namespace UAC
{

using namespace Common;

namespace Engine
{


void PrintString(std::string &str)
{
	std::cout << str;
}



void SetActiveScene(INodeScene& scene)
{
	LOG(DEBUG)("SetActive (%s)", scene.GetScriptName());

	g_pSceneManager->SetActive(&scene);
}


void RegisterGlobalFunctions(asIScriptEngine* engine)
{
	int r;

	r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(PrintString), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("uint GetSystemTime()", asFUNCTION(timeGetTime), asCALL_STDCALL); assert(r >= 0);

	r = engine->RegisterGlobalFunction("void SetActiveScene(const Scene &in)", asFUNCTION(SetActiveScene), asCALL_CDECL); assert(r >= 0);
}


} // namespace Engine
} // namespace UAC

#endif // USE_ASLIB
