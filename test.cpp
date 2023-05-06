#include "configMockNm.h"
#include <iostream>
#define CALLBACK_PARAMS_TEMPLATE GObject* srcObject, GAsyncResult* result, gpointer userData

extern ConfigMockNM configMockNM;

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
	// When the client inits
	NMClient* client;
	nm_client_new_async(NULL, clientReadyCallback, &client);

	std::cout << "Client is " << client << std::endl;

	// Then the client ptr should be MOCK_VALID_CLIENT
	assertTrue(client == (NMClient*)MOCK_VALID_CLIENT, "Client should be valid");
}

int main()
{
	test_client_initialization();
	return 0;
}
