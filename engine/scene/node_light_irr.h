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
	{
		//TODO: utilizzare valori del costruttore

		LOG(DEBUG)("ADD     Light (%s)", _sName.c_str());
	}


	//! Destructor
	virtual ~NodeLightIrr()
	{
		LOG(DEBUG)("DELETE  Light (%s)", _sName.c_str());
	}
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_IRRLIB

#endif // __UAC__NODE_LIGHT_IRR_H
