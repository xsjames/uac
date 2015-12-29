//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================

#ifndef __UAC__GFXDEFINES_H
#define __UAC__GFXDEFINES_H

#include "core/types.h"

namespace UAC
{
namespace Common
{


struct GraphicResolution
{
	int32_t Width;
	int32_t Height;
	int32_t ColorDepth;

	GraphicResolution()
		: Width(0)
		, Height(0)
		, ColorDepth(0)
	{}

	GraphicResolution(int32_t width, int32_t height, int32_t color_depth)
	{
		Width = width;
		Height = height;
		ColorDepth = color_depth;
	}
};


struct DisplayMode : public GraphicResolution
{
	int32_t RefreshRate;
	bool    Vsync;
	bool    Windowed;

	DisplayMode()
		: RefreshRate(0)
		, Vsync(false)
		, Windowed(false)
	{}

	DisplayMode(const GraphicResolution &res, bool windowed, int32_t refresh, bool vsync)
		: GraphicResolution(res)
		, RefreshRate(refresh)
		, Vsync(vsync)
		, Windowed(windowed)
	{}
};


} // namespace Common
} // namespace UAC

#endif // __UAC__GFXDEFINES_H
