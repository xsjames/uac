//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Scene
//
//=============================================================================

#ifdef USE_ASLIB

#include <assert.h>  // assert()
#include "script/script_as_scene.h"
#include "scene/scene_manager.h"
#include "scene/node_mesh.h"
#include "debug/out.h"


extern UAC::Common::ISceneManager* g_pSceneManager;


namespace UAC
{

using namespace Common;

namespace Engine
{

//TODO lo scriptname � utile per la fase di sviluppo e debug, poi si vedr� se manternerlo
static INodeScene* Scene_Factory(const std::string& scriptname)
{
	LOG(DEBUG)("Scene_Factory");
	INodeScene* node = g_pSceneManager->CreateSceneNode(0, scriptname);
	g_pSceneManager->Add(node);
	return node;
}

static INodeScene *Scene_FactoryCopy(const INodeScene& other)
{
	// non viene mai chiamata ???
	assert(1);
	return 0;
}

void Scene_AddRef(INodeScene* obj)
{
	LOG(DEBUG)("Scene_GRAB (%s)", obj->GetScriptName());
	obj->grab();
}

void Scene_Release(INodeScene* obj)
{
	LOG(DEBUG)("Scene_DROP (%s)", obj->GetScriptName());
	int r = obj->getRefCounter();
	if(r == 1)
	{
		g_pSceneManager->Remove(obj);
	}
	else
	{
		obj->drop();
	}
}


void Scene_SetPosition(float x, float y, float z, INodeScene* obj)
{
	LOG(DEBUG)("Scene_SetPosition (%s)", obj->GetScriptName());
	obj->SetPosition(vector3f(x, y, z));
}

void Scene_SetRotation(float x, float y, float z, INodeScene* obj)
{
	LOG(DEBUG)("Scene_SetRotation (%s)", obj->GetScriptName());
	obj->SetRotation(vector3f(x, y, z));
}

void Scene_SetScale(float x, float y, float z, INodeScene* obj)
{
	LOG(DEBUG)("Scene_SetScale (%s)", obj->GetScriptName());
	obj->SetScale(vector3f(x, y, z));
}


void RegisterScene(asIScriptEngine* engine)
{
	int r;

	r = engine->RegisterObjectType("Scene", 0, asOBJ_REF); assert(r >= 0);
	// with reference types we register factores and not constructors
	r = engine->RegisterObjectBehaviour("Scene", asBEHAVE_FACTORY, "Scene @f(string &in)", asFUNCTION(Scene_Factory), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Scene", asBEHAVE_FACTORY, "Scene @f(const Scene &in)", asFUNCTION(Scene_FactoryCopy), asCALL_CDECL); assert(r >= 0);
	// Registering the addref/release behaviours
	r = engine->RegisterObjectBehaviour("Scene", asBEHAVE_ADDREF, "void f()", asFUNCTION(Scene_AddRef), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Scene", asBEHAVE_RELEASE, "void f()", asFUNCTION(Scene_Release), asCALL_CDECL_OBJLAST); assert(r >= 0);
	// Registering the other behaviours
	r = engine->RegisterObjectMethod("Scene", "void SetPosition(float, float, float)", asFUNCTION(Scene_SetPosition), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Scene", "void SetRotation(float, float, float)", asFUNCTION(Scene_SetRotation), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Scene", "void SetScale(float, float, float)", asFUNCTION(Scene_SetScale), asCALL_CDECL_OBJLAST); assert(r >= 0);
	//
	r = engine->RegisterObjectMethod("Scene", "Color GetAmbientLight()", asMETHODPR(INodeScene, GetAmbientLight, (void) const, const Color&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Scene", "void SetAmbientLight(const Color &in)", asMETHODPR(INodeScene, SetAmbientLight, (const Color&), void), asCALL_THISCALL); assert(r >= 0);
}


} // namespace Engine
} // namespace UAC

#endif // USE_ASLIB
