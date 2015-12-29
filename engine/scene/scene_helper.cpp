//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Scene Manager creation helper
//
//=============================================================================

#include "scene/scene_helper.h"
#ifdef USE_IRRLIB
#include "scene/scene_manager_irr.h"
#endif


namespace UAC
{

using namespace Common;

namespace Engine
{

bool CreateSceneManager(ISceneManager** manager)
{
#ifdef USE_IRRLIB
	*manager = new SceneManagerIrr();
	return *manager ? true : false;
#endif

	return false;
}

void DestroySceneManager(ISceneManager** manager)
{
	if(*manager)
	{
		delete *manager;
		*manager = 0;
	}
}

/*
bool CreateNodeScene(Common::ISceneManager* mgr)
{
	return false;
}

bool CreateNodeCamera(Common::INode* parent, Common::ISceneManager* mgr)
{
	return false;
}

bool CreateNodeLight(Common::INode* parent, Common::ISceneManager* mgr)
{
	return false;
}

bool CreateNodeMesh(Common::INode* parent, Common::ISceneManager* mgr)
{
	return false;
}
*/

} // namespace Engine
} // namespace UAC
