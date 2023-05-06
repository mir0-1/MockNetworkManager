#pragma once
#include "IntentionalFailureSupportedObject.h"
#include <NetworkManager.h>

#define MOCK_VALID_CLIENT (NMClient*)0x1
#define MOCK_INVALID_CLIENT (NMClient*)0x0

class MockClient : public IntentionalFailureSupportedObject
{
	private:
		NMClient* client;
		MockConnectionStorage connectionStorage;
		MockDeviceStorage deviceStorage;

	public:
		NMClient* getClient() const;
		MockConnectionStorage& getConnectionStorage();
		MockDeviceStorage& getDeviceStorage();

		MockClient();
};
