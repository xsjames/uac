//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Device interface
//
//=============================================================================

#ifndef __UAC__DEVICE_H
#define __UAC__DEVICE_H

#include "device/gfxdriver.h"


namespace UAC
{
namespace Common
{

class IDevice
{
public:
	IDevice()
		: _gfxdriver(0)
	{}

	virtual ~IDevice() {}

	virtual const char* GetName() = 0;
	virtual const char* GetID() = 0;

	virtual bool Init() = 0;
	
	virtual bool InitGFX(const DisplayMode &mode) = 0;
	IGFXDriver* GetGFXDriver() { return _gfxdriver; }


	//! Runs the device. Returns false if device wants to be deleted.
	virtual bool Run() = 0;


protected:
	IGFXDriver* _gfxdriver;


	/*
	virtual void SetTintMethod(TintMethod method) = 0;
	virtual IGfxModeList *GetSupportedModeList(int color_depth) = 0;
	virtual bool IsModeSupported(const DisplayMode &mode) = 0;
	virtual DisplayMode GetDisplayMode() const = 0;
	virtual IGfxFilter *GetGraphicsFilter() const = 0;
	virtual Rect GetRenderDestination() const = 0;
	virtual void SetCallbackForPolling(GFXDRV_CLIENTCALLBACK callback) = 0;
	virtual void SetCallbackToDrawScreen(GFXDRV_CLIENTCALLBACK callback) = 0;
	virtual void SetCallbackOnInit(GFXDRV_CLIENTCALLBACKINITGFX callback) = 0;
	// The NullSprite callback is called in the main render loop when a
	// null sprite is encountered. You can use this to hook into the rendering
	// process.
	virtual void SetCallbackForNullSprite(GFXDRV_CLIENTCALLBACKXY callback) = 0;
	virtual void UnInit() = 0;
	virtual void ClearRectangle(int x1, int y1, int x2, int y2, RGB *colorToUse) = 0;
	virtual Common::Bitmap *ConvertBitmapToSupportedColourDepth(Common::Bitmap *bitmap) = 0;
	virtual IDriverDependantBitmap* CreateDDBFromBitmap(Common::Bitmap *bitmap, bool hasAlpha, bool opaque = false) = 0;
	virtual void UpdateDDBFromBitmap(IDriverDependantBitmap* bitmapToUpdate, Common::Bitmap *bitmap, bool hasAlpha) = 0;
	virtual void DestroyDDB(IDriverDependantBitmap* bitmap) = 0;
	virtual void ClearDrawList() = 0;
	virtual void DrawSprite(int x, int y, IDriverDependantBitmap* bitmap) = 0;
	virtual void SetScreenTint(int red, int green, int blue) = 0;
	virtual void SetRenderOffset(int x, int y) = 0;
	virtual void RenderToBackBuffer() = 0;
	virtual void Render() = 0;
	virtual void Render(GlobalFlipType flip) = 0;
	virtual void GetCopyOfScreenIntoBitmap(Common::Bitmap *destination) = 0;
	virtual void EnableVsyncBeforeRender(bool enabled) = 0;
	virtual void Vsync() = 0;
	virtual void FadeOut(int speed, int targetColourRed, int targetColourGreen, int targetColourBlue) = 0;
	virtual void FadeIn(int speed, PALETTE p, int targetColourRed, int targetColourGreen, int targetColourBlue) = 0;
	virtual void BoxOutEffect(bool blackingOut, int speed, int delay) = 0;
	virtual bool PlayVideo(const char *filename, bool useAVISound, VideoSkipType skipType, bool stretchToFullScreen) = 0;
	virtual void UseSmoothScaling(bool enabled) = 0;
	virtual bool SupportsGammaControl() = 0;
	virtual void SetGamma(int newGamma) = 0;
	virtual Common::Bitmap* GetMemoryBackBuffer() = 0;
	virtual void SetMemoryBackBuffer(Common::Bitmap *backBuffer) = 0;
	virtual bool RequiresFullRedrawEachFrame() = 0;
	virtual bool HasAcceleratedStretchAndFlip() = 0;
	virtual bool UsesMemoryBackBuffer() = 0;
	*/
};

} // namespace Common
} // namespace UAC


#endif // __UAC__DEVICE_H
