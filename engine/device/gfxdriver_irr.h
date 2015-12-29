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

#ifndef __UAC__GFXDRIVER_IRR_H
#define __UAC__GFXDRIVER_IRR_H

#ifdef USE_IRRLIB

#include "device/gfxdriver.h"


namespace UAC
{
namespace Engine
{

class GFXDriverIrr : public Common::IGFXDriver
{
public:
	GFXDriverIrr()
		: _vdriver(0)
		, _guienv(0)
	{}

	~GFXDriverIrr();

	virtual const char* GetName() { return "Irrlicht Engine - EDTSW"; }
	virtual const char* GetID() { return "IRR"; }

	virtual bool Init(const Common::DisplayMode& mode) { return true; }
	virtual bool InitIrr(irr::IrrlichtDevice* _irr);

	virtual void Render();


protected:
	irr::video::IVideoDriver* _vdriver;
	irr::scene::ISceneManager* _smgr;
	irr::gui::IGUIEnvironment* _guienv;

/*
	bool _autoVsync;
	Bitmap *_allegroScreenWrapper;
	Bitmap *virtualScreen;
	Bitmap *_spareTintingScreen;
	GFXDRV_CLIENTCALLBACK _callback;
	GFXDRV_CLIENTCALLBACK _drawScreenCallback;
	GFXDRV_CLIENTCALLBACKXY _nullSpriteCallback;
	GFXDRV_CLIENTCALLBACKINITGFX _initGfxCallback;
	int _tint_red, _tint_green, _tint_blue;

	ALSoftwareBitmap* drawlist[MAX_DRAW_LIST_SIZE];
	int drawx[MAX_DRAW_LIST_SIZE], drawy[MAX_DRAW_LIST_SIZE];
	int numToDraw;
	GFX_MODE_LIST *_gfxModeList;

	#ifdef _WIN32
	IDirectDrawGammaControl* dxGammaControl;
	// The gamma ramp is a lookup table for each possible R, G and B value
	// in 32-bit colour (from 0-255) it maps them to a brightness value
	// from 0-65535. The default gamma ramp just multiplies each value by 256
	DDGAMMARAMP gammaRamp;
	DDGAMMARAMP defaultGammaRamp;
	DDCAPS ddrawCaps;
	#endif

	void highcolor_fade_out(int speed, int targetColourRed, int targetColourGreen, int targetColourBlue);
	void highcolor_fade_in(Bitmap *bmp_orig, int speed, int targetColourRed, int targetColourGreen, int targetColourBlue);
	void __fade_from_range(PALLETE source, PALLETE dest, int speed, int from, int to) ;
	void __fade_out_range(int speed, int from, int to, int targetColourRed, int targetColourGreen, int targetColourBlue) ;
	int  GetAllegroGfxDriverID(bool windowed);
	*/
};

} // namespace Engine
} // namespace UAC

#endif // USE_IRRLIB

#endif // __UAC__GFXDRIVER_IRR_H
