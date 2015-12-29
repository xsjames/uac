//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC INodeMesh
//
//=============================================================================
#ifndef __UAC__NODE_MESH_H
#define __UAC__NODE_MESH_H

#include "scene/node.h"



namespace UAC
{
namespace Common
{


class INodeMesh : public virtual INode
{
public:
	//! Constructor
	INodeMesh(INode* parent, ISceneManager* mgr, const std::string& filename, const std::string& scriptname, int id = -1)
		: INode(parent, mgr, id)
		, _fileName(filename), _shadow(false), _clickable(true)
	{
		SetScriptName(scriptname);
	}


	//! Destructor
	virtual ~INodeMesh() {}
	

	//! Returns type of the scene node
	virtual SCENE_NODE_TYPE GetType() const { return SNT_MESH; }
	
	
	//! Returns the filename of the mesh.
	virtual const char* GetMeshFileName() const { return _fileName.c_str(); }
	/*
	//! Sets the filename of the mesh.
	virtual void SetMeshFileName(const char* filename) { _fileName = filename; }
	virtual void SetMeshFileName(const std::string& filename) { _fileName = filename; }
	*/
	
	//! Returns the name of the mesh.
	virtual const char* GetName() const { return _name.c_str(); }

	//! Sets the name of the mesh.
	virtual void SetName(const char* name) { _name = name; }
	virtual void SetName(const std::string& name) { _name = name; }

	
	//! Gets whether the object's shadow is visible or not.
	virtual bool GetShadow() const { return _shadow; }

	//! Sets whether the object's shadow is visible or not.
	virtual void SetShadow(bool state) { _shadow = state; }

	
	//! Returns the mesh clickable state.
	bool IsClickable() const { return _clickable; }

	//! Sets the mesh clickable state.
	void SetClickable(bool active) { _clickable = active; }

	
	//! Reads attributes of the light node.
	virtual bool DeserializeAttributes(pugi::xml_node& xmlnode)
	{
		INode::DeserializeAttributes(xmlnode);
		
		_fileName = xmlnode.attribute("FileName").value();
		_name = xmlnode.attribute("Name").value();
		_shadow = xmlnode.attribute("Shadow").as_bool();
		_clickable = xmlnode.attribute("Clickable").as_bool();

		return true;
	}


protected:
	std::string _fileName;			//! File name of the mesh.
	std::string _name;				//! Name of the mesh.
	bool _shadow;					//! Whether the object's shadow should be visible or not.
	bool _clickable;				//! Whether the objecs is recognised as something which the player can interact with.
};


}   // namespace Common
}   // namespace UAC

#endif // __UAC__NODE_MESH_H
