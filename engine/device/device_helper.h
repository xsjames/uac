//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
// Device creation helper
//
//=============================================================================

#ifndef __UAC__DEVICE_HELPER_H
#define __UAC__DEVICE_HELPER_H

#include "device/device.h"


namespace UAC
{
namespace Engine
{

bool CreateDevice(Common::IDevice** device);
void DestroyDevice(Common::IDevice** device);

} // namespace Engine
} // namespace UAC


#endif // __UAC__DEVICE_HELPER_H
