//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// INode
//
// The base class type of all objects that sit in the scene graph. Provides
// members for transform (translation, rotation, scale), appearance (visibility)
// and hierarchy (parent, children).
//
//=============================================================================
#ifndef __UAC__NODE_H
#define __UAC__NODE_H

#include <string>
#include <vector>
#include <assert.h>
#include "scene/node_types.h"
#include "core/vector3.h"
#include "core/color.h"

//TEMP
#include "xml/pugixml.hpp"


namespace UAC
{
namespace Common
{

class ISceneManager;

class INode
{
public:
	//! Constructor
	INode(INode* parent, ISceneManager* mgr, int id = -1)
		: _parent(parent), _mgr(mgr)
		, _ID(id), _refCounter(1)
	{
		if(_parent)
			_parent->AddChild(this);

		//updateAbsolutePosition();
	}


	//! Destructor
	virtual ~INode()
	{
		// delete all children
		RemoveAllChildren();
	}
	

	//! Returns type of the scene node
	virtual SCENE_NODE_TYPE GetType() const { return SNT_UNKNOWN; }


	//! Retrieve the scene manager for this node.
	virtual ISceneManager* GetSceneManager() const { return _mgr; }
	//! Sets the new scene manager for this node and all children.
	void SetSceneManager(ISceneManager* newManager)
	{
		_mgr = newManager;
		
		for(std::vector<INode*>::iterator it = _children.begin() ; it != _children.end(); ++it)
			(*it)->SetSceneManager(newManager);
	}


	//! Returns the name of the node.
	virtual const char* GetScriptName() const { return _sName.c_str(); }
	//! Sets the name of the node.
	virtual void SetScriptName(const char* name) { _sName = name; }
	virtual void SetScriptName(const std::string& name) { _sName = name; }


	//! Get the id of the scene node.
	virtual int GetID() const { return _ID; }
	//! Sets the id of the scene node.
	virtual void SetID(int id) { _ID = id; }


	//! Gets the position of the node relative to its parent.
	virtual const vector3f& GetPosition() = 0;
	//! Sets the position of the node relative to its parent.
	virtual void SetPosition(const vector3f& position) = 0;


	//! Gets the rotation of the node relative to its parent.
	virtual const vector3f& GetRotation() = 0;
	//! Sets the rotation (in degrees) of the node relative to its parent.
	virtual void SetRotation(const vector3f& rotation) = 0;


	//! Gets the scale of the scene node relative to its parent.
	virtual const vector3f& GetScale() = 0;
	//! Sets the relative scale of the scene node.
	virtual void SetScale(const vector3f& scale) = 0;

	
	//! Returns whether the node should be visible (if all of its parents are visible).
	virtual bool IsVisible() const { return _visible; }
	//! Sets if the node should be visible or not.
	// All children of this node won't be visible either, when set to false.
	virtual void SetVisible(bool isVisible) { _visible = isVisible; }

	//! Check whether the node is truly visible, taking into accounts its parents' visibility
	virtual bool IsTrulyVisible() const
	{
		if(!_visible)
			return false;

		if(!_parent)
			return true;

		return _parent->IsTrulyVisible();
	}


	//! Adds a child to this scene node.
	//! If the child node already has a parent it is first removed from the other parent.
	virtual void AddChild(INode* child)
	{
		if(child && (child != this))
		{
			// Change scene manager
			if (_mgr != child->_mgr)
				child->SetSceneManager(_mgr);

			if(child->GetParent() && (child->GetParent() != this))
			{
				// remove from old parent
				child->grab();
				child->RemoveFromScene();
			}
			child->_parent = this;

			_children.push_back(child);
		}
	}
	
	//! Removes a child from this scene node.
	virtual bool RemoveChild(INode* child)
	{
		for(std::vector<INode*>::iterator it = _children.begin(); it != _children.end(); ++it)
		{
			if((*it) == child)
			{
				(*it)->_parent = 0;
				(*it)->drop();
				_children.erase(it);
				return true;
			}
		}

		return false;
	}

	//! Removes all children of this scene node.
	virtual void RemoveAllChildren()
	{
		for(std::vector<INode*>::iterator it = _children.begin(); it != _children.end(); ++it)
		{
			(*it)->_parent = 0;
			(*it)->drop();
		}

		_children.clear();
	}
	
	//! Removes this scene node from the scene.
	virtual void RemoveFromScene()
	{
		if (_parent)
			_parent->RemoveChild(this);
	}
	
	//! Returns a const reference to the list of all children.
	const std::vector<INode*>& GetChildren() const
	{
		return _children;
	}


	//! Renders the node.
	virtual void Render() = 0;


	//! Returns the parent of this scene node
	virtual INode* GetParent() { return _parent; }
	//! Changes the parent of the scene node.
	virtual void SetParent(INode* newParent)
	{
		grab();
		RemoveFromScene();

		_parent = newParent;

		if(_parent)
			_parent->AddChild(this);

		drop();
	}


	//! Writes attributes of the node.
	/// Implement this to expose the attributes of your node for scripting
	// languages, editors, debuggers or xml serialization purposes.
	//virtual bool SerializeAttributes(pugi::xml_node& xmlnode) const = 0;

	//! Reads attributes of the node.
	// Implement this to set the attributes of your scene node for scripting
	// languages, editors, debuggers or xml deserialization purposes.
	virtual bool DeserializeAttributes(pugi::xml_node& xmlnode)
	{
		_visible = xmlnode.attribute("Visible").as_bool();
		_sName = xmlnode.attribute("ScriptName").value();
		/*
		_position.set(xmlnode.attribute("Position").value());
		_rotation.set(xmlnode.attribute("Rotation").value());
		_scale.set(xmlnode.attribute("Scale").value());
		*/
		return true;
	}


	//! Grabs the object. Increments the reference counter by one.
	void grab() const { ++_refCounter; }
	//! Drops the object. Decrements the reference counter by one.
	bool drop() const
	{
		// someone is doing bad reference counting.
		assert(_refCounter > 0);

		--_refCounter;
		if (!_refCounter)
		{
			delete this;
			return true;
		}

		return false;
	}
	//! Returns the reference counter (DEBUG)
	int getRefCounter() { return _refCounter; }


protected:
	ISceneManager* _mgr;			//! Pointer to the scene manager.
	
	INode* _parent;					//! Pointer to the parent.
	std::vector<INode*> _children;	//! List of all children of this node.

	bool _visible;					//! Is the node visible?

	int _ID;						//! ID of the node.
	std::string _sName;				//! Script name of the node.


private:
	//! The reference counter. Mutable to do reference counting on const objects.
	mutable int _refCounter;


	

	
	/*
	//! Gets the absolute position of the node in world coordinates.
	virtual vector3f GetAbsolutePosition() const = 0;


	//! OnAnimate() is called just before rendering the whole scene.
	/** Nodes may calculate or store animations here, and may do other useful things,
	depending on what they are. Also, OnAnimate() should be called for all
	child scene nodes here. This method will be called once per frame, independent
	of whether the scene node is visible or not.
	\param timeMs Current time in milliseconds. *
	virtual void OnAnimate(u32 timeMs)
	{
		if (IsVisible)
		{
			// animate this node with all animators

			INodeAnimatorList::Iterator ait = Animators.begin();
			while (ait != Animators.end())
				{
				// continue to the next node before calling animateNode()
				// so that the animator may remove itself from the scene
				// node without the iterator becoming invalid
				INodeAnimator* anim = *ait;
				++ait;
				anim->animateNode(this, timeMs);
			}

			// update absolute position
			updateAbsolutePosition();

			// perform the post render process on all children

			INodeList::Iterator it = Children.begin();
			for (; it != Children.end(); ++it)
				(*it)->OnAnimate(timeMs);
		}
	}

	//! Get the axis aligned, not transformed bounding box of this node.
	/** This means that if this node is an animated 3d character,
	moving in a room, the bounding box will always be around the
	origin. To get the box in real world coordinates, just
	transform it with the matrix you receive with
	getAbsoluteTransformation() or simply use
	getTransformedBoundingBox(), which does the same.
	\return The non-transformed bounding box. *
	virtual const aabbox3d<f32>& getBoundingBox() const = 0;


	//! Get the axis aligned, transformed and animated absolute bounding box of this node.
	/** \return The transformed bounding box. *
	virtual const aabbox3d<f32> getTransformedBoundingBox() const
	{
		aabbox3d<f32> box = getBoundingBox();
		AbsoluteTransformation.transformBoxEx(box);
		return box;
	}


	//! Get the absolute transformation of the node. Is recalculated every OnAnimate()-call.
	//! \return The absolute transformation matrix.
	virtual const matrix4& getAbsoluteTransformation() const
	{
		return AbsoluteTransformation;
	}


	//! Returns the relative transformation of the scene node.
	/** The relative transformation is stored internally as 3
	vectors: translation, rotation and scale. To get the relative
	transformation matrix, it is calculated from these values.
	\return The relative transformation matrix. *
	virtual matrix4 getRelativeTransformation() const
	{
		matrix4 mat;
		mat.setRotationDegrees(RelativeRotation);
		mat.setTranslation(RelativeTranslation);

		if (RelativeScale != vector3f(1.f,1.f,1.f))
		{
			matrix4 smat;
			smat.setScale(RelativeScale);
			mat *= smat;
		}

		return mat;
	}


	//! Adds an animator which should animate this node.
	/** \param animator A pointer to the new animator. *
	virtual void addAnimator(INodeAnimator* animator)
	{
		if (animator)
		{
			Animators.push_back(animator);
			animator->grab();
		}
	}


	//! Get a list of all scene node animators.
	/** \return The list of animators attached to this node. *
	const list<INodeAnimator*>& getAnimators() const
	{
		return Animators;
	}


	//! Removes an animator from this scene node.
	/** If the animator is found, it is also dropped and might be
	deleted if not other grab exists for it.
	\param animator A pointer to the animator to be deleted. *
	virtual void removeAnimator(INodeAnimator* animator)
	{
		INodeAnimatorList::Iterator it = Animators.begin();
		for (; it != Animators.end(); ++it)
		{
			if ((*it) == animator)
			{
				(*it)->drop();
				Animators.erase(it);
				return;
			}
		}
	}


	//! Removes all animators from this scene node.
	/** The animators might also be deleted if no other grab exists
	for them. *
	virtual void removeAnimators()
	{
		INodeAnimatorList::Iterator it = Animators.begin();
		for (; it != Animators.end(); ++it)
			(*it)->drop();

		Animators.clear();
	}


	//! Returns the material based on the zero based index i.
	/** To get the amount of materials used by this scene node, use
	getMaterialCount(). This function is needed for inserting the
	node into the scene hierarchy at an optimal position for
	minimizing renderstate changes, but can also be used to
	directly modify the material of a scene node.
	\param num Zero based index. The maximal value is getMaterialCount() - 1.
	\return The material at that index. *
	virtual video::SMaterial& getMaterial(u32 num)
	{
		return video::IdentityMaterial;
	}


	//! Get amount of materials used by this scene node.
	/** \return Current amount of materials of this scene node. *
	virtual u32 getMaterialCount() const
	{
		return 0;
	}


	//! Sets all material flags at once to a new value.
	/** Useful, for example, if you want the whole mesh to be
	affected by light.
	\param flag Which flag of all materials to be set.
	\param newvalue New value of that flag. *
	void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue)
	{
		for (u32 i=0; i<getMaterialCount(); ++i)
			getMaterial(i).setFlag(flag, newvalue);
	}


	//! Sets the texture of the specified layer in all materials of this scene node to the new texture.
	/** \param textureLayer Layer of texture to be set. Must be a
	value smaller than MATERIAL_MAX_TEXTURES.
	\param texture New texture to be used. *
	void setMaterialTexture(u32 textureLayer, video::ITexture* texture)
	{
		if (textureLayer >= video::MATERIAL_MAX_TEXTURES)
			return;

		for (u32 i=0; i<getMaterialCount(); ++i)
			getMaterial(i).setTexture(textureLayer, texture);
	}


	//! Sets the material type of all materials in this scene node to a new material type.
	/** \param newType New type of material to be set. *
	void setMaterialType(video::E_MATERIAL_TYPE newType)
	{
		for (u32 i=0; i<getMaterialCount(); ++i)
			getMaterial(i).MaterialType = newType;
	}



	//! Enables or disables automatic culling based on the bounding box.
	/** Automatic culling is enabled by default. Note that not
	all SceneNodes support culling and that some nodes always cull
	their geometry because it is their only reason for existence,
	for example the OctreeSceneNode.
	\param state The culling state to be used. *
	void setAutomaticCulling( E_CULLING_TYPE state)
	{
		AutomaticCullingState = state;
	}


	//! Gets the automatic culling state.
	/** \return The automatic culling state. *
	E_CULLING_TYPE getAutomaticCulling() const
	{
		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
		return AutomaticCullingState;
	}


	//! Returns the triangle selector attached to this scene node.
	/** The Selector can be used by the engine for doing collision
	detection. You can create a TriangleSelector with
	ISceneManager::createTriangleSelector() or
	ISceneManager::createOctreeTriangleSelector and set it with
	INode::setTriangleSelector(). If a scene node got no triangle
	selector, but collision tests should be done with it, a triangle
	selector is created using the bounding box of the scene node.
	\return A pointer to the TriangleSelector or 0, if there
	is none. *
	virtual ITriangleSelector* getTriangleSelector() const
	{
		return TriangleSelector;
	}


	//! Sets the triangle selector of the scene node.
	/** The Selector can be used by the engine for doing collision
	detection. You can create a TriangleSelector with
	ISceneManager::createTriangleSelector() or
	ISceneManager::createOctreeTriangleSelector(). Some nodes may
	create their own selector by default, so it would be good to
	check if there is already a selector in this node by calling
	INode::getTriangleSelector().
	\param selector New triangle selector for this scene node. *
	virtual void setTriangleSelector(ITriangleSelector* selector)
	{
		if (TriangleSelector != selector)
		{
			if (TriangleSelector)
				TriangleSelector->drop();

			TriangleSelector = selector;
			if (TriangleSelector)
				TriangleSelector->grab();
		}
	}


	//! Updates the absolute position based on the relative and the parents position
	/** Note: This does not recursively update the parents absolute positions, so if you have a deeper
		hierarchy you might want to update the parents first.*
	virtual void updateAbsolutePosition()
	{
		if (Parent)
		{
			AbsoluteTransformation =
				Parent->getAbsoluteTransformation() * getRelativeTransformation();
		}
		else
			AbsoluteTransformation = getRelativeTransformation();
	}
	*/
};


}   // namespace Common
}   // namespace UAC

#endif // __UAC__NODE_H
