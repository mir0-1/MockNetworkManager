#pragma once
#include "MockDevice.h"
#include <NetworkManager.h>
#include <glib.h>

class MockDeviceStorage
{
	private:
		GPtrArray* devices;

	public:
		void addDevice(MockDevice* device);
		void freeDevices(bool reinit);
		GPtrArray* getDevices() const;

		MockDeviceStorage();
		~MockDeviceStorage();
};
