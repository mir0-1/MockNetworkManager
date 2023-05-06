#include "MockDevice.h"

NMDeviceType MockDevice::getType() const
{
	return type;
}

MockDevice::MockDevice(NMDeviceType type)
{
	this->type = type;
}
