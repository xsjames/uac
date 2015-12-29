//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Scene Manager creation helper
//
//=============================================================================

#ifndef __UAC__SCENE_HELPER_H
#define __UAC__SCENE_HELPER_H

#include "scene/scene_manager.h"


namespace UAC
{
namespace Engine
{

bool CreateSceneManager(Common::ISceneManager** manager);
void DestroySceneManager(Common::ISceneManager** manager);

/*
bool CreateNodeScene(Common::ISceneManager* mgr);
bool CreateNodeCamera(Common::INode* parent, Common::ISceneManager* mgr);
bool CreateNodeLight(Common::INode* parent, Common::ISceneManager* mgr);
bool CreateNodeMesh(Common::INode* parent, Common::ISceneManager* mgr);
*/

} // namespace Engine
} // namespace UAC


#endif // __UAC__SCENE_HELPER_H
