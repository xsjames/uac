//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Camera
//
//=============================================================================

#ifdef USE_ASLIB

#include <assert.h>  // assert()
#include "script/script_as_camera.h"
#include "scene/scene_manager.h"
#include "scene/node_camera.h"
#include "debug/out.h"


extern UAC::Common::ISceneManager* g_pSceneManager;


namespace UAC
{

using namespace Common;

namespace Engine
{

//TODO lo scriptname è utile per la fase di sviluppo e debug, poi si vedrà se manternerlo
static INodeCamera* Camera_Factory(INodeScene* parent, const std::string& scriptname)
{
	LOG(DEBUG)("Camera_Factory");
	INodeCamera* node = g_pSceneManager->CreateCameraNode(parent, scriptname);
	if (parent)
		node->grab(); // add the reference of the parent in the script
	return node;
}

static INodeCamera *Camera_FactoryCopy(const INodeCamera& other)
{
	// non viene mai chiamata ???
	assert(1);
	return 0;
}

void Camera_AddRef(INodeCamera* obj)
{
	LOG(DEBUG)("Camera_GRAB (%s)", obj->GetScriptName());
	obj->grab();
}

void Camera_Release(INodeCamera* obj)
{
	LOG(DEBUG)("Camera_DROP (%s)", obj->GetScriptName());
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


void Camera_SetPosition(float x, float y, float z, INodeCamera* obj)
{
	LOG(DEBUG)("Camera_SetPosition (%s)", obj->GetScriptName());
	obj->SetPosition(vector3f(x, y, z));
}

void Camera_SetRotation(float x, float y, float z, INodeCamera* obj)
{
	LOG(DEBUG)("Camera_SetRotation (%s)", obj->GetScriptName());
	obj->SetRotation(vector3f(x, y, z));
}

void Camera_SetScale(float x, float y, float z, INodeCamera* obj)
{
	LOG(DEBUG)("Camera_SetScale (%s)", obj->GetScriptName());
	obj->SetScale(vector3f(x, y, z));
}


void RegisterCamera(asIScriptEngine* engine)
{
	int r;

	r = engine->RegisterObjectType("Camera", 0, asOBJ_REF); assert(r >= 0);
	// with reference types we register factores and not constructors
	r = engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera @f(const Scene &in, string &in)", asFUNCTION(Camera_Factory), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera @f(const Camera &in)", asFUNCTION(Camera_FactoryCopy), asCALL_CDECL); assert(r >= 0);
	// Registering the addref/release behaviours
	r = engine->RegisterObjectBehaviour("Camera", asBEHAVE_ADDREF, "void f()", asFUNCTION(Camera_AddRef), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Camera", asBEHAVE_RELEASE, "void f()", asFUNCTION(Camera_Release), asCALL_CDECL_OBJLAST); assert(r >= 0);
	// Registering the assignment behaviour
	//r = engine->RegisterObjectMethod("Camera", "Mesh &opAssign(const Mesh &in)", asMETHODPR(Oggetto, operator =, (const Oggetto&), Oggetto&), asCALL_THISCALL); assert(r >= 0);
	// Registering the other behaviours
	r = engine->RegisterObjectMethod("Camera", "void SetPosition(float, float, float)", asFUNCTION(Camera_SetPosition), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Camera", "void SetRotation(float, float, float)", asFUNCTION(Camera_SetRotation), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Camera", "void SetScale(float, float, float)", asFUNCTION(Camera_SetScale), asCALL_CDECL_OBJLAST); assert(r >= 0);
	//r = engine->RegisterGlobalFunction("void Print(const Mesh &in)", asFUNCTION(Oggetto_Print), asCALL_CDECL); assert(r >= 0);
}


} // namespace Engine
} // namespace UAC

#endif // USE_ASLIB
