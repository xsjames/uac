//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Light
//
//=============================================================================

#ifdef USE_ASLIB

#include <assert.h>  // assert()
#include "script/script_as_light.h"
#include "scene/scene_manager.h"
#include "scene/node_light.h"
#include "debug/out.h"


extern UAC::Common::ISceneManager* g_pSceneManager;


namespace UAC
{

using namespace Common;

namespace Engine
{

//TODO lo scriptname è utile per la fase di sviluppo e debug, poi si vedrà se manternerlo
static INodeLight* Light_Factory(LIGHT_TYPE type, const std::string& scriptname)
{
	LOG(DEBUG)("Light_Factory");
	return g_pSceneManager->CreateLightNode(g_pSceneManager->GetRoot(), type, scriptname);
}

static INodeLight *Light_FactoryCopy(const INodeLight& other)
{
	// non viene mai chiamata ???
	assert(1);
	return 0;
}

void Light_AddRef(INodeLight* obj)
{
	LOG(DEBUG)("Light_GRAB (%s)", obj->GetScriptName());
	obj->grab();
}

void Light_Release(INodeLight* obj)
{
	LOG(DEBUG)("Light_DROP (%s)", obj->GetScriptName());
	int r = obj->getRefCounter();
	if(r == 1 && obj->GetParent())
	{
		obj->RemoveFromScene();
	}
	else
	{
		obj->drop();
	}
}


void Light_SetPosition(float x, float y, float z, INodeLight* obj)
{
	LOG(DEBUG)("Light_SetPosition (%s)", obj->GetScriptName());
	obj->SetPosition(vector3f(x, y, z));
}

void Light_SetDirection(float x, float y, float z, INodeLight* obj)
{
	LOG(DEBUG)("Light_SetDirection (%s)", obj->GetScriptName());
	obj->SetRotation(vector3f(x, y, z));
}



void RegisterLight(asIScriptEngine* engine)
{
	int r;

	// register enum LIGHT_TYPE
	r = engine->RegisterEnum("LIGHT_TYPE"); assert(r >= 0);
	r = engine->RegisterEnumValue("LIGHT_TYPE", "LT_DIRECTIONAL", (int)LT_DIRECTIONAL); assert(r >= 0);
	r = engine->RegisterEnumValue("LIGHT_TYPE", "LT_POINT", (int)LT_POINT); assert(r >= 0);

	// register class Light
	r = engine->RegisterObjectType("Light", 0, asOBJ_REF); assert(r >= 0);
	// with reference types we register factores and not constructors
	r = engine->RegisterObjectBehaviour("Light", asBEHAVE_FACTORY, "Light @f(LIGHT_TYPE, string &in)", asFUNCTION(Light_Factory), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Light", asBEHAVE_FACTORY, "Light @f(const Light &in)", asFUNCTION(Light_FactoryCopy), asCALL_CDECL); assert(r >= 0);
	// Registering the addref/release behaviours
	r = engine->RegisterObjectBehaviour("Light", asBEHAVE_ADDREF, "void f()", asFUNCTION(Light_AddRef), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Light", asBEHAVE_RELEASE, "void f()", asFUNCTION(Light_Release), asCALL_CDECL_OBJLAST); assert(r >= 0);
	// Registering the assignment behaviour
	//r = engine->RegisterObjectMethod("Light", "Mesh &opAssign(const Mesh &in)", asMETHODPR(Oggetto, operator =, (const Oggetto&), Oggetto&), asCALL_THISCALL); assert(r >= 0);
	// Registering the other behaviours
	r = engine->RegisterObjectMethod("Light", "void SetPosition(float, float, float)", asFUNCTION(Light_SetPosition), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Light", "void SetDirection(float, float, float)", asFUNCTION(Light_SetDirection), asCALL_CDECL_OBJLAST); assert(r >= 0);
	//r = engine->RegisterGlobalFunction("void Print(const Mesh &in)", asFUNCTION(Oggetto_Print), asCALL_CDECL); assert(r >= 0);
}


} // namespace Engine
} // namespace UAC

#endif // USE_ASLIB
