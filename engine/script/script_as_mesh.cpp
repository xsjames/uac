//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Mesh
//
//=============================================================================

#ifdef USE_ASLIB

#include <assert.h>  // assert()
#include "script/script_as_mesh.h"
#include "scene/scene_manager.h"
#include "scene/node_mesh.h"
#include "debug/out.h"


extern UAC::Common::ISceneManager* g_pSceneManager;


namespace UAC
{

using namespace Common;

namespace Engine
{

//TODO lo scriptname è utile per la fase di sviluppo e debug, poi si vedrà se manternerlo
static INodeMesh* Mesh_Factory(INodeScene* parent, const std::string& filename, const std::string& scriptname)
{
	LOG(DEBUG)("Mesh_Factory");
	INodeMesh* node = g_pSceneManager->CreateMeshNode(parent, filename, scriptname);
	if (parent)
		node->grab(); // add the reference of the parent in the script
	return node;
}

static INodeMesh *Mesh_FactoryCopy(const INodeMesh& other)
{
	// non viene mai chiamata ???
	assert(1);
	return 0;
}

void Mesh_AddRef(INodeMesh* obj)
{
	LOG(DEBUG)("Mesh_GRAB (%s)", obj->GetScriptName());
	obj->grab();
}

void Mesh_Release(INodeMesh* obj)
{
	LOG(DEBUG)("Mesh_DROP (%s)", obj->GetScriptName());
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


void Mesh_SetPosition(float x, float y, float z, INodeMesh* obj)
{
	LOG(DEBUG)("Mesh_SetPosition (%s)", obj->GetScriptName());
	obj->SetPosition(vector3f(x, y, z));
}

void Mesh_SetRotation(float x, float y, float z, INodeMesh* obj)
{
	LOG(DEBUG)("Mesh_SetRotation (%s)", obj->GetScriptName());
	obj->SetRotation(vector3f(x, y, z));
}

void Mesh_SetScale(float x, float y, float z, INodeMesh* obj)
{
	LOG(DEBUG)("Mesh_SetScale (%s)", obj->GetScriptName());
	obj->SetScale(vector3f(x, y, z));
}


void RegisterMesh(asIScriptEngine* engine)
{
	int r;

	r = engine->RegisterObjectType("Mesh", 0, asOBJ_REF); assert(r >= 0);
	// with reference types we register factores and not constructors
	r = engine->RegisterObjectBehaviour("Mesh", asBEHAVE_FACTORY, "Mesh @f(const Scene &in, string &in, string &in)", asFUNCTION(Mesh_Factory), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Mesh", asBEHAVE_FACTORY, "Mesh @f(const Mesh &in)", asFUNCTION(Mesh_FactoryCopy), asCALL_CDECL); assert(r >= 0);
	// Registering the addref/release behaviours
	r = engine->RegisterObjectBehaviour("Mesh", asBEHAVE_ADDREF, "void f()", asFUNCTION(Mesh_AddRef), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Mesh", asBEHAVE_RELEASE, "void f()", asFUNCTION(Mesh_Release), asCALL_CDECL_OBJLAST); assert(r >= 0);
	// Registering the assignment behaviour
	//r = engine->RegisterObjectMethod("Mesh", "Mesh &opAssign(const Mesh &in)", asMETHODPR(Oggetto, operator =, (const Oggetto&), Oggetto&), asCALL_THISCALL); assert(r >= 0);
	// Registering the other behaviours
	r = engine->RegisterObjectMethod("Mesh", "void SetPosition(float, float, float)", asFUNCTION(Mesh_SetPosition), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Mesh", "void SetRotation(float, float, float)", asFUNCTION(Mesh_SetRotation), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Mesh", "void SetScale(float, float, float)", asFUNCTION(Mesh_SetScale), asCALL_CDECL_OBJLAST); assert(r >= 0);
	//r = engine->RegisterGlobalFunction("void Print(const Mesh &in)", asFUNCTION(Oggetto_Print), asCALL_CDECL); assert(r >= 0);
}


} // namespace Engine
} // namespace UAC

#endif // USE_ASLIB
