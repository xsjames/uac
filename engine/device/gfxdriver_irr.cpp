//=============================================================================
//
// Adventure Game Studio (AGS)
//
// Copyright (C) 1999-2011 Chris Jones and 2011-20xx others
// The full list of copyright holders can be found in the Copyright.txt
// file, which is part of this source code distribution.
//
// The AGS source code is provided under the Artistic License 2.0.
// A copy of this license can be found in the file License.txt and at
// http://www.opensource.org/licenses/artistic-license-2.0.php
//
//=============================================================================
//
// Irrlicht Interface for UAC GFX driver
//
//=============================================================================

#ifdef USE_IRRLIB
#include <irrlicht.h>
#include "device/gfxdriver_irr.h"

using namespace irr;


namespace UAC
{

using namespace Common;

namespace Engine
{

GFXDriverIrr::~GFXDriverIrr()
{
}

bool GFXDriverIrr::InitIrr(irr::IrrlichtDevice* _irr)
{
	_vdriver = _irr->getVideoDriver();
	_smgr = _irr->getSceneManager();
	_guienv = _irr->getGUIEnvironment();

	//TEMP
	_guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", core::rect<s32>(10,10,260,22), true);

	return true;
}


void GFXDriverIrr::Render()
{
	_vdriver->beginScene(true, true, video::SColor(255,153,217,234));

	_smgr->drawAll();
	_guienv->drawAll();

	_vdriver->endScene();
}

} // namespace Engine
} // namespace UAC

#endif // USE_IRRLIB
