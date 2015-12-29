//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Irrlicht Interface for UAC INodeMesh
//
//=============================================================================
#ifndef __UAC__NODE_MESH_IRR_H
#define __UAC__NODE_MESH_IRR_H

#ifdef USE_IRRLIB

#include "scene/node_irr.h"
#include "scene/node_mesh.h"
#include "debug/out.h"


namespace UAC
{
namespace Engine
{


class NodeMeshIrr : public Common::INodeMesh, public INodeIrr
{
public:
	//! Constructor
	NodeMeshIrr(Common::INode* parent, Common::ISceneManager* mgr, const std::string& filename, const std::string& scriptname, int id = -1,
			const Common::vector3f& position = Common::vector3f(0,0,0),
			const Common::vector3f& rotation = Common::vector3f(0,0,0),
			const Common::vector3f& scale = Common::vector3f(1.0f, 1.0f, 1.0f))
		: Common::INode(parent, mgr, id)
		, Common::INodeMesh(parent, mgr, filename, scriptname, id)
		, INodeIrr()
	{
		//TODO: utilizzare valori del costruttore

		LOG(DEBUG)("ADD     Mesh (%s)", GetScriptName());
	} 


	//! Destructor
	virtual ~NodeMeshIrr()
	{
		LOG(DEBUG)("DELETE  Mesh (%s)", GetScriptName());
	}
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_IRRLIB

#endif // __UAC__NODE_MESH_IRR_H
