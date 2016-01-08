//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Irrlicht Interface for UAC INodeLight
//
//=============================================================================
#ifndef __UAC__NODE_LIGHT_IRR_H
#define __UAC__NODE_LIGHT_IRR_H

#ifdef USE_IRRLIB

#include "scene/node_irr.h"
#include "scene/node_light.h"
#include "debug/out.h"


namespace UAC
{
namespace Engine
{


class NodeLightIrr : public Common::INodeLight, public INodeIrr
{
public:
	//! Constructor
	NodeLightIrr(Common::INode* parent, Common::ISceneManager* mgr, Common::LIGHT_TYPE type, const std::string& scriptname, int id = -1,
			const Common::vector3f& position = Common::vector3f(0,0,0),
			const Common::vector3f& rotation = Common::vector3f(0,0,0))
		: Common::INode(parent, mgr, id)
		, Common::INodeLight(parent, mgr, type, scriptname, id)
		, INodeIrr()
		, _color(255, 255, 255, 255)
	{
		//TODO: utilizzare valori del costruttore

		LOG(DEBUG)("ADD     Light (%s)", _sName.c_str());
	}


	//! Destructor
	virtual ~NodeLightIrr()
	{
		LOG(DEBUG)("DELETE  Light (%s)", _sName.c_str());
	}


	//! Gets the light color.
	virtual const Common::Color& GetColor() const { return _color; }
	//! Sets the light color.
	virtual void SetColor(const Common::Color& color)
	{
		LOG(DEBUG)("Light_SetColor (%s)", GetScriptName());
		_color = color;

		irr::video::SColorf c(irr::video::SColor(255, color.r, color.g, color.b));

		((irr::scene::ILightSceneNode*)_node_irr)->getLightData().DiffuseColor = c;
		// set some useful specular color
		((irr::scene::ILightSceneNode*)_node_irr)->getLightData().SpecularColor = c.getInterpolated(irr::video::SColor(255, 255, 255, 255), 0.7f);
	}


protected:
	Common::Color _color;					//! Color of the light.
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_IRRLIB

#endif // __UAC__NODE_LIGHT_IRR_H
