#include "MockAccessPoint.h"

const std::string& MockAccessPoint::getSSID() const
{
	return ssid;
}

const std::string& MockAccessPoint::getPSK() const
{
	return psk;
}

NM80211ApSecurityFlags MockAccessPoint::getRSNFlags() const
{
	return rsnFlags;
}

MockAccessPoint::MockAccessPoint(const std::string& ssid, const std::string& psk = "", rsnFlags = NM_802_11_AP_SEC_NONE)
{
	this->ssid = ssid;
	this->psk = psk;
	this->rsnFlags = rsnFlags;
}
