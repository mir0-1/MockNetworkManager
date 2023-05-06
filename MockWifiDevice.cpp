#include "MockWifiDevice.h"

GPtrArray* MockWifiDevice::getAccessPoints() const
{
	return accessPoints;
}

MockAccessPoint* MockWifiDevice::addAccessPoint(const std::string& ssid, const std::string& psk, NM80211ApSecurityFlags flags)
{
	MockAccessPoint* accessPoint = new MockAccessPoint(ssid, psk, flags);
	g_ptr_array_add(accessPoints, (gpointer)accessPoint);
}

void MockWifiDevice::removeAccessPoint(MockAccessPoint* accessPoint)
{
	g_ptr_array_remove(accessPoints, (gpointer)accessPoint);
}

void MockWifiDevice::freeAccessPoints(bool reinit)
{
	for (int i = 0; i < accessPoints->len; i++)
		delete (MockAccessPoint*)accessPoints->pdata[i];

	g_ptr_array_unref(accessPoints);

	if (reinit)
		accessPoints = g_ptr_array_new();
}

MockWifiDevice::MockWifiDevice() : MockDevice(NM_DEVICE_TYPE_WIFI)
{
	accessPoints = g_ptr_array_new();
}

~MockWifiDevice::MockWifiDevice()
{
	freeAccessPoints(false);
}
