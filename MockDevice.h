#pragma once
#include <NetworkManager.h>

class MockDevice
{
	private:
		NMDeviceType type;

	public:
		NMDeviceType getType() const;

		MockDevice(NMDeviceType type);
};
