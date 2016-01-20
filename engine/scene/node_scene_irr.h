//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Irrlicht Interface for UAC INodeScene
//
//=============================================================================
#ifndef __UAC__NODE_SCENE_IRR_H
#define __UAC__NODE_SCENE_IRR_H

#ifdef USE_IRRLIB

#include "scene/node_irr.h"
#include "scene/node_scene.h"
#include "debug/out.h"


namespace UAC
{
namespace Engine
{


class NodeSceneIrr : public Common::INodeScene, public INodeIrr
{
public:
	//! Constructor
	NodeSceneIrr(Common::INode* parent, Common::ISceneManager* mgr, const std::string& scriptname, int id = -1,
			const Common::vector3f& position = Common::vector3f(0, 0, 0),
			const Common::vector3f& rotation = Common::vector3f(0, 0, 0),
			const Common::vector3f& scale = Common::vector3f(1.0f, 1.0f, 1.0f))
		: Common::INode(parent, mgr, id)
		, Common::INodeScene(parent, mgr, scriptname, id)
		, INodeIrr()
		, _activeCamera(0), _ambientLight(255, 255, 255, 255)
	{
		//TODO: utilizzare valori del costruttore

		LOG(DEBUG)("ADD     Scene (%s)", _sName.c_str());
	}

	//! Destructor
	virtual ~NodeSceneIrr()
	{
		LOG(DEBUG)("DELETE  Scene (%s)", _sName.c_str());
	}


	//! Sets the scene active state
	virtual void SetActive(bool active);


	//! Gets the currently active camera.
	virtual Common::INodeCamera* GetActiveCamera() const { return _activeCamera; }
	//! Sets the active camera used to render the scene.
	virtual void SetActiveCamera(Common::INodeCamera* camera);


	//! Gets the ambient light color.
	virtual const Common::Color& GetAmbientLight() const { return _ambientLight; }
	//! Sets the ambient light color.
	virtual void SetAmbientLight(const Common::Color& color)
	{
		LOG(DEBUG)("Scene_SetAmbientLight (%s)", GetScriptName());
		_ambientLight = color;

		if(IsActive())
		{
			_setAMbientLightIrr();
		}
	}


protected:
	Common::Color _ambientLight;			//! The light that doesn't come from any particular direction. All the objects in the scene will be lit up by the ambient light.
	Common::INodeCamera* _activeCamera;		//! The currently active camera used to render the scene.


private:
	void _setActiveCameraIrr();
	void _setAMbientLightIrr();
};


}   // namespace Engine
}   // namespace UAC

#endif // USE_IRRLIB

#endif // __UAC__NODE_SCENE_IRR_H
