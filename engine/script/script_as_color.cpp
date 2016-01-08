//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Script interface - Color
//
//=============================================================================

#ifdef USE_ASLIB

#include <assert.h>  // assert()
#include <new>
#include "script/script_as_color.h"
#include "core/color.h"
#include "debug/out.h"


namespace UAC
{

using namespace Common;

namespace Engine
{


static void ConstructColor(Color *thisPointer)
{
	new(thisPointer) Color();
}

static void CopyConstructColor(const Color &other, Color *thisPointer)
{
	new(thisPointer) Color(other);
}

static void ConstructColorFromInts(int r, int g, int b, void *thisPointer)
{
	new(thisPointer) Color(r, g, b);
}

static void ConstructColorFromInts(int a, int r, int g, int b, void *thisPointer)
{
	new(thisPointer) Color(a, r, g, b);
}

static void DestructColor(Color *thisPointer)
{
	thisPointer->~Color();
}




void RegisterColor(asIScriptEngine* engine)
{
	int r;

	// register the color type
#if AS_CAN_USE_CPP11
	// With C++11 it is possible to use asGetTypeTraits to automatically determine the correct flags to use
	r = engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asGetTypeTraits<Color>()); assert(r >= 0);
#else
	r = engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); assert(r >= 0);
#endif


	// Register the object operator overloads
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructColor), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color &in)", asFUNCTION(CopyConstructColor), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(uint8, uint8, uint8)", asFUNCTIONPR(ConstructColorFromInts, (int, int, int, void*), void), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(uint8, uint8, uint8, uint8)", asFUNCTIONPR(ConstructColorFromInts, (int, int, int, int, void*), void), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructColor), asCALL_CDECL_OBJLAST); assert(r >= 0);

	r = engine->RegisterObjectMethod("Color", "Color &opAssign(const Color &in)", asMETHODPR(Color, operator =, (const Color&), Color&), asCALL_THISCALL); assert(r >= 0);

	r = engine->RegisterObjectProperty("Color", "float r", asOFFSET(Color, r)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Color", "float g", asOFFSET(Color, g)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Color", "float b", asOFFSET(Color, b)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Color", "float a", asOFFSET(Color, a)); assert(r >= 0);
}


} // namespace Engine
} // namespace UAC

#endif // USE_ASLIB
