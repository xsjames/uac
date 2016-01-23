//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Irrlicht Interface for scene nodes
//
//=============================================================================
#ifndef __UAC__NODE_IRR_H
#define __UAC__NODE_IRR_H

#ifdef USE_IRRLIB

#include <irrlicht.h>
#include "scene/node.h"
#include "debug/out.h"


namespace UAC
{
namespace Engine
{


class INodeIrr : public virtual Common::INode
{
public:
	//! Constructor
	INodeIrr()
		: Common::INode(0, 0)
		, _node_irr(0)
	{
	}

	//! Destructor
	virtual ~INodeIrr()
	{
	}


	//! Retrieve the node address in Irrlicht scene manager.
	virtual irr::scene::ISceneNode* GetNodeIrr() const { return _node_irr; }
	//! Retrieve the node address in Irrlicht scene manager.
	virtual void SetNodeIrr(irr::scene::ISceneNode* node) { _node_irr = node; }


	//! Gets the position of the node relative to its parent.
	virtual const Common::vector3f& GetPosition()
	{
		_position = Common::vector3f(_node_irr->getPosition().X, _node_irr->getPosition().Y, _node_irr->getPosition().Z);
		return _position;
	}

	//! Sets the position of the node relative to its parent.
	virtual void SetPosition(const Common::vector3f& position)
	{
		_node_irr->setPosition(irr::core::vector3df(position.X, position.Y, position.Z));
	}


	//! Gets the rotation of the node relative to its parent.
	virtual const Common::vector3f& GetRotation()
	{
		_rotation = Common::vector3f(_node_irr->getRotation().X, _node_irr->getRotation().Y, _node_irr->getRotation().Z);
		return _rotation;
	}

	//! Sets the rotation (in degrees) of the node relative to its parent.
	virtual void SetRotation(const Common::vector3f& rotation)
	{
		_node_irr->setRotation(irr::core::vector3df(rotation.X, rotation.Y, rotation.Z));
	}


	//! Gets the scale of the scene node relative to its parent.
	virtual const Common::vector3f& GetScale()
	{
		_scale = Common::vector3f(_node_irr->getScale().X, _node_irr->getScale().Y, _node_irr->getScale().Z);
		return _scale;
	}

	//! Sets the relative scale of the scene node.
	virtual void SetScale(const Common::vector3f& scale)
	{
		_node_irr->setScale(irr::core::vector3df(scale.X, scale.Y, scale.Z));
	}


	//! Removes this scene node from the scene.
	virtual void RemoveFromScene()
	{
		// removes from Irrlicht engine
		_node_irr->remove();
		// remove from INode
		INode::RemoveFromScene();
	}


	virtual void Render()
	{
		LOG(DEBUG)("RENDER  Irr (%s)", _sName.c_str()); //TEMP
	}


protected:
	irr::scene::ISceneNode* _node_irr;		//! Irrlicht's node pointer.

	Common::vector3f _position;				//! Position of the node relative to its parent.
	Common::vector3f _rotation;				//! Rotation of the node relative to its parent.
	Common::vector3f _scale;				//! Scale of the node relative to its parent.
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_IRRLIB

#endif // __UAC__NODE_SCENE_IRR_H
