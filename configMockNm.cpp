#include "configMockNm.h"

void ConfigMockNM::freeArrElement(gpointer element, gpointer userData)
{
	g_object_unref((GObject*)element);
}

NMClient* ConfigMockNM::getClient()
{
	return client;
}

void ConfigMockNM::setClientValid()
{
	client = MOCK_VALID_CLIENT;
}

void ConfigMockNM::setClientInvalid()
{
	client = MOCK_INVALID_CLIENT;
}

NMConnectivityState ConfigMockNM::getConnectivityState()
{
	return connectivityState;
}

void ConfigMockNM::setConnectivityState(NMConnectivityState newConnectivityState)
{
	connectivityState = newConnectivityState;
}

NMActiveConnecton* ConfigMockNM::getActiveConnection()
{
	return activeConnection;
}

void ConfigMockNM::resetActiveConnectionState()
{
	g_object_set((GObject*)activeConnection, NM_ACTIVE_CONNECTION_STATE, NM_ACTIVE_CONNECTION_STATE_UNKNOWN, NULL);
}

GPtrArray* ConfigMockNM::getDevices()
{
	return devices;
}

void ConfigMockNM::addDevice(NMDevice* device)
{
	if (device == NULL)
		return;
	g_ptr_array_add(devices, device);
}

void ConfigMockNM::resetArrayContents(GPtrArray** arr, bool freeInternals, bool reinit)
{
	if (arr == NULL || *arr == NULL)
		return;

	if (freeInternals)
		g_ptr_array_foreach(*arr, (GFunc)freeArrElement, NULL);

	g_ptr_array_unref(*arr);
	*arr = NULL;
	
	if (reinit)
		*arr = g_ptr_array_new();
}

GPtrArray* ConfigMockNM::getConnections()
{
	return connections;
}

void ConfigMockNM::addConnection(NMConnection* connection)
{
	g_ptr_array_add(connections, connection);
}

ConfigMockNM::ConfigMockNM()
{
	client = MOCK_INVALID_CLIENT;
	connectivityState = NM_CONNECTIVITY_NONE;
	devices = g_ptr_array_new();
	connections = g_ptr_array_new();
	accessPoints = g_ptr_array_new();
	activeConnection = (NMActiveConnecton*)g_object_new(NM_TYPE_ACTIVE_CONNECTION, NM_ACTIVE_CONNECTION_STATE, NM_ACTIVE_CONNECTION_STATE_UNKNOWN, NULL);
}

ConfigMockNM::~ConfigMockNM()
{
	if (devices != NULL)
		g_ptr_array_unref(devices);

	if (connections != NULL)
		g_ptr_array_unref(connections);

	g_object_unref(activeConnection);
}

bool ConfigMockNM::getFailActivation()
{
	return failActivation;
}

void ConfigMockNM::setFailActivation(bool value)
{
	failActivation = value;
}

GPtrArray* ConfigMockNM::getAccessPoints()
{
	retrun accessPoints;
}

void ConfigMockNM::addAccessPoint(NMAccessPoint* accessPoint)
{
	g_ptr_array_add(accessPoints, accessPoint);
}
