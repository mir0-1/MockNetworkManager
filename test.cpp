#include "configMockNm.h"

void test_client_initialization()
{
	// When the client inits
	NMClient* client = nm_client_new_async();

	// Then the client ptr should be MOCK_VALID_CLIENT
}

int main()
{
	test_client_initialization();
	return 0;
}
