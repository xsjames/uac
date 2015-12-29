//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC INodeLight
//
//=============================================================================
#ifndef __UAC__NODE_LIGHT_H
#define __UAC__NODE_LIGHT_H

#include "scene/node.h"



namespace UAC
{
namespace Common
{

enum LIGHT_TYPE
{
	LT_POINT,
	LT_SPOT,
	LT_DIRECTIONAL
};


class INodeLight : public virtual INode
{
public:
	//! Constructor
	INodeLight(INode* parent, ISceneManager* mgr, LIGHT_TYPE type, const std::string& scriptname, int id = -1)
		: INode(parent, mgr, id)
		, _lType(type)
		, _color(255,255,255,255)
		, _radius(100.f)
		, _distance(0)
		, _castShadow(false)
	{
		SetScriptName(scriptname);
	}


	//! Destructor
	virtual ~INodeLight() {}


	//! Returns type of the scene node
	virtual SCENE_NODE_TYPE GetType() const { return SNT_LIGHT; }


	//! Gets the light type.
	virtual LIGHT_TYPE GetLightType() const { return _lType; }
	//! Sets the light type.
	virtual void SetLightType(LIGHT_TYPE type) { _lType = type; }


	//! Gets the light color.
	virtual const Color& GetColor() const { return _color; }
	//! Sets the light color.
	virtual void SetColor(const Color& color) { _color = color; }


	//! Gets the light radius of influence.
	virtual float GetRadius() const { return _radius; }
	//! Sets the light radius of influence.
	virtual void SetRadius(float radius) { _radius = radius; }
	

	//! Gets the light distance.
	virtual float GetDistance() const { return _distance; }
	//! Sets the light distance.
	virtual void SetDistance(float distance) { _distance = distance; }


	//! Gets whether this light casts shadows.
	virtual bool GetCastShadow() const { return _castShadow; }
	//! Sets whether this light casts shadows.
	virtual void SetCastShadow(bool state) { _castShadow = state; }

	
	//! Reads attributes of the light node.
	virtual bool DeserializeAttributes(pugi::xml_node& xmlnode)
	{
		INode::DeserializeAttributes(xmlnode);
		
		_lType = (LIGHT_TYPE)xmlnode.attribute("LightType").as_int();
		_color.set(xmlnode.attribute("Color").value());
		_radius = xmlnode.attribute("Radius").as_float();
		_distance = xmlnode.attribute("Distance").as_float();
		_castShadow = xmlnode.attribute("CastShadow").as_bool();

		return true;
	}


protected:
	LIGHT_TYPE _lType;				//! Light type.
	Color _color;					//! Color of the light.
	float _radius;					//! Light's radius of influence.
	float _distance;				//! ???
	bool _castShadow;				//! Whether this light casts shadows.
};


}   // namespace Common
}   // namespace UAC

#endif // __UAC__NODE_LIGHT_H
