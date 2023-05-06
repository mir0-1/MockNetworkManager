#include "MockDevice.h"
#include "MockAccessPoint.h"
#include <glib.h>

class MockWifiDevice : public MockDevice
{
	private:
		GPtrArray* accessPoints;

	public:
		GPtrArray* getAccessPoints() const;
		MockAccessPoint* addAccessPoint(const std::string& ssid, const std::string& psk = "", NM80211ApSecurityFlags flags = NM_802_11_AP_SEC_NONE);
		void removeAccessPoint(MockAccessPoint* accessPoint);
		void freeAccessPoints(bool reinit);

		MockWifiDevice();
		~MockWifiDevice();
}
