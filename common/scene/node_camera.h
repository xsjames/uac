//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC INodeCamera 
//
//=============================================================================
#ifndef __UAC__NODE_CAMERA_H
#define __UAC__NODE_CAMERA_H

#include "scene/node.h"



namespace UAC
{
namespace Common
{


class INodeCamera : public virtual INode
{
public:
	//! Constructor
	INodeCamera(INode* parent, ISceneManager* mgr, const std::string& scriptname, int id = -1)
		: INode(parent, mgr, id)
	{
		SetScriptName(scriptname);
	}


	//! Destructor
	virtual ~INodeCamera() {}
	

	//! Returns type of the scene node
	virtual SCENE_NODE_TYPE GetType() const { return SNT_CAMERA; }
	
	/*
	//! Gets the camera direction.
	virtual const vector3f& GetDirection() const = 0;

	//! Sets the camera direction.
	virtual void SetDirection(const vector3f& direction) = 0;
	*/

	//! Reads attributes of the light node.
	virtual bool DeserializeAttributes(pugi::xml_node& xmlnode)
	{
		INode::DeserializeAttributes(xmlnode);
		/*
		_direction.set(xmlnode.attribute("Direction").value());
		*/
		return true;
	}
};


}   // namespace Common
}   // namespace UAC

#endif // __UAC__NODE_CAMERA_H
