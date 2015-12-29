//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Irrlicht Interface for UAC INodeCamera 
//
//=============================================================================
#ifndef __UAC__NODE_CAMERA_IRR_H
#define __UAC__NODE_CAMERA_IRR_H

#ifdef USE_IRRLIB

#include "scene/node_irr.h"
#include "scene/node_camera.h"
#include "debug/out.h"


namespace UAC
{
namespace Engine
{


class NodeCameraIrr : public Common::INodeCamera, public INodeIrr
{
public:
	//! Constructor
	NodeCameraIrr(Common::INode* parent, Common::ISceneManager* mgr, int id = -1,
		const Common::vector3f& position = Common::vector3f(0, 0, 0),
		const Common::vector3f& rotation = Common::vector3f(0, 0, 0),
		const Common::vector3f& scale = Common::vector3f(1.0f, 1.0f, 1.0f))
		: Common::INode(parent, mgr, id)
		, Common::INodeCamera(parent, mgr, id)
		, INodeIrr()
	{
		//TODO: utilizzare i valori nel costruttore

		LOG(DEBUG)("ADD     Camera (%s)", _sName.c_str());
	}

	//! Destructor
	virtual ~NodeCameraIrr()
	{
		LOG(DEBUG)("DELETE  Camera (%s)", _sName.c_str());
	}
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_IRRLIB

#endif // __UAC__NODE_CAMERA_IRR_H
