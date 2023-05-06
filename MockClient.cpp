#include "MockClient.h"

NMClient* MockClient::getClient() const
{
	return client;
}

MockConnectionStorage& MockClient::getConnectionStorage()
{
	return connectionStorage;
}

MockDeviceStorage& MockClient::getDeviceStorage()
{
	return deviceStorage;
}

MockClient::MockClient()
{
	bool failOnPurpose = getFailOnPurpose();

	if (failOnPurpose)
		client = MOCK_INVALID_CLIENT;
	else
		client = MOCK_INVALID_CLIENT;
}
