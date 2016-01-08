//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC INodeScene
//
//=============================================================================
#ifndef __UAC__NODE_SCENE_H
#define __UAC__NODE_SCENE_H

#include "scene/node.h"



namespace UAC
{
namespace Common
{


class INodeScene : public virtual INode
{
public:
	//! Constructor
	INodeScene(INode* parent, ISceneManager* mgr, const std::string& scriptname, int id = -1)
		: INode(parent, mgr, id)
		, _active(false), _inputActive(false)
		, _shadow(false)
		, _shadowColor(128,0,0,0)
	{
		SetScriptName(scriptname);
	}


	//! Destructor
	virtual ~INodeScene() {}
	

	//! Returns type of the scene node
	virtual SCENE_NODE_TYPE GetType() const { return SNT_SCENE; }


	//! Returns the scene active state
	bool IsActive() const { return _active; }
	//! Sets the scene active state
	void SetActive(bool active) { _active = active; }
	

	//! Returns the scene input state
	bool IsInputActive() const { return _inputActive; }
	//! Sets the scene input state
	void SetInputActive(bool active) { _inputActive = active; }
	

	//! Gets the ambient light color.
	virtual const Color& GetAmbientLight() const = 0;
	//! Sets the ambient light color.
	virtual void SetAmbientLight(const Color& color) = 0;

	
	//! Gets whether the scene's shadow is visible or not.
	virtual bool GetShadow() const { return _shadow; }
	//! Sets whether the scene's shadow is visible or not.
	virtual void SetShadow(bool state) { _shadow = state; }

	
	//! Gets the shadow color.
	virtual const Color& GetShadowColor() const { return _shadowColor; }
	//! Sets the shadow color.
	virtual void SetShadowColor(const Color& color) { _shadowColor = color; }

	
	//! Returns the filename of the walk area.
	virtual const char* GetWalkArea() const { return _walkArea.c_str(); }
	//! Sets the filename of the walk area.
	virtual void SetWalkArea(const char* filename) { _walkArea = filename; }
	virtual void SetWalkArea(const std::string& filename) { _walkArea = filename; }

	
	//! Reads attributes of the light node.
	virtual bool DeserializeAttributes(pugi::xml_node& xmlnode)
	{
		INode::DeserializeAttributes(xmlnode);


		_shadow = xmlnode.attribute("ShadowVisible").as_bool();
		_shadowColor.set(xmlnode.attribute("ShadowColor").value());
		_walkArea = xmlnode.attribute("WalkableArea").value();

		return true;
	}


protected:
	bool _active;					//! Is the scene in active state.
	bool _inputActive;				//! Is the scene input active.

	bool _shadow;					//! Whether the scene's shadow should be visible or not.
	Color _shadowColor;				//! Color of the shadows.
	std::string _walkArea;			//! Name of the walk area file.
};


}   // namespace Common
}   // namespace UAC

#endif // __UAC__NODE_SCENE_H
