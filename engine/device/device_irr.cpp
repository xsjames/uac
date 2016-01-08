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
// Irrlicht Interface for UAC device
//
//=============================================================================

#ifdef USE_IRRLIB
#include "device/device_irr.h"
#include "device/gfxdriver_irr.h"

using namespace irr;


namespace UAC
{

using namespace Common;

namespace Engine
{

DeviceIrr::~DeviceIrr()
{
	if(_gfxdriver)
	{
		delete _gfxdriver;
	}

	if(_irr)
	{
		_irr->drop();
	}
}

bool DeviceIrr::Init()
{
	return true;
}

bool DeviceIrr::InitGFX(const DisplayMode& mode)
{
	_irr = createDevice(video::EDT_DIRECT3D9, core::dimension2d<u32>(mode.Width, mode.Height), mode.ColorDepth, !mode.Windowed, false, false, 0);
	if(!_irr)
	{
		return false;
	}

	_gfxdriver = new GFXDriverIrr();
	_gfxdriver->Init(mode);
	//
	if(strcmp(_gfxdriver->GetID(), "IRR") == 0)
		((GFXDriverIrr*)_gfxdriver)->InitIrr(_irr);

	return true;
}

bool DeviceIrr::Run()
{
	return _irr->run();
}

} // namespace Engine
} // namespace UAC

#endif // USE_IRRLIB
