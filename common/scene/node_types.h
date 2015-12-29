//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC Node types definition
//
//=============================================================================
#ifndef __UAC__NODE_TYPES_H
#define __UAC__NODE_TYPES_H


//! XML scene nodes name
#define XMLNT_SCENE			"scene"
#define XMLNT_CAMERA		"camera"
#define XMLNT_LIGHT			"light"
#define XMLNT_MESH			"mesh"



namespace UAC
{
namespace Common
{

	//! An enumeration for all types of built-in scene nodes
	enum SCENE_NODE_TYPE
	{
		//! Scene node
		SNT_SCENE,

		//! Camera node
		SNT_CAMERA,

		//! Light node
		SNT_LIGHT,

		//! Mesh node
		SNT_MESH,

		//! Empty node
		SNT_EMPTY,

		//! Unknown node
		SNT_UNKNOWN,

		//! Will match with any node when checking types
		SNT_ANY
	};

}   // namespace Common
}   // namespace AGS

#endif // __UAC__NODE_TYPES_H
