#include "MockClient.h"
#include <iostream>
#define CALLBACK_PARAMS_TEMPLATE GObject* srcObject, GAsyncResult* result, gpointer userData

extern MockClient mockClient;

void assertTrue(bool condition, const std::string& assertname)
{
	std::cout << "Asserting " << assertname;

	if (condition)
		std::cout << ": Successful" << std::endl;
	else
		std::cout << ": Failed" << std::endl;
}

void clientReadyCallback(CALLBACK_PARAMS_TEMPLATE)
{
	*((NMClient**)userData) = nm_client_new_finish(result, NULL);
}

void test_client_initialization()
{
	// Given
	mockClient.setFailOnPurpose(false);

	// When
	NMClient* client;
	nm_client_new_async(NULL, clientReadyCallback, &client);

	// Then
	assertTrue(client == (NMClient*)MOCK_VALID_CLIENT, "Client should be valid");
}

int main()
{
	test_client_initialization();
	return 0;
}
