#include "configMockNm.h"
#include <iostream>
#define CALLBACK_PARAMS_TEMPLATE GObject* srcObject, GAsyncResult* result, gpointer userData

template <class T>
void assertEquals(T a, T b, std::string& assertname)
{
	std::cout << "Asserting " << assertname << std::endl;

	if (a == b)
		std::cout << "Successful" << std::endl;
	else
		std::cout << "Failed" << std::endl;
}

void test_client_initialization()
{
	// When the client inits
	NMClient* client;
	nm_client_new_async(NULL, clientReadyCallback, &client);

	// Then the client ptr should be MOCK_VALID_CLIENT
	assertEquals(client, MOCK_VALID_CLIENT, "Client should be valid");
}

void clientReadyCallback(CALLBACK_PARAMS_TEMPLATE)
{
	*client = nm_client_new_async_finish(result, NULL);
}

int main()
{
	test_client_initialization();
	return 0;
}
