#pragma once
#include <string>
#include <NetworkManager.h>

class MockAccessPoint
{
	private:
		std::string ssid;
		std::string psk;
		NM80211ApSecurityFlags rsnFlags;

	public:
		const std::string& getSSID() const;
		const std::string& getPSK() const;
		NM80211ApSecurityFlags getRSNFlags() const;

		MockAccessPoint(const std::string& ssid, const std::string& psk, NM80211ApSecurityFlags rsnFlags);
};
