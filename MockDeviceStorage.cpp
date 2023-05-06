#include "MockDeviceStorage.h"

void MockDeviceStorage::addDevice(MockDevice* device)
{
	if (device == NULL)
		return;

	g_ptr_array_add(devices, (gpointer)device);
}

void MockDeviceStorage::freeDevices(bool reinit)
{
	for (int i = 0; i < devices->len; i++)
		delete (MockDevice*)devices->pdata[i];

	g_ptr_array_unref(devices);

	if (reinit)
		devices = g_ptr_array_new();
}

GPtrArray* MockDeviceStorage::getDevices() const
{
	return devices;
}

MockDeviceStorage::MockDeviceStorage()
{
	devices = g_ptr_array_new();
}

MockDeviceStorage::~MockDeviceStorage()
{
	freeDevices(false);
}
