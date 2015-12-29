//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Device creation helper
//
//=============================================================================

#include "device/device_helper.h"
#ifdef USE_IRRLIB
#include "device/device_irr.h"
#endif


namespace UAC
{

using namespace Common;

namespace Engine
{

bool CreateDevice(IDevice** device)
{
#ifdef USE_IRRLIB
	*device = new DeviceIrr();
	return *device ? true : false;
#endif

	return false;
}

void DestroyDevice(IDevice** device)
{
	if(*device)
	{
		delete *device;
		*device = 0;
	}
}

} // namespace Engine
} // namespace UAC
