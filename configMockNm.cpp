#include "configMockNm.h"

void ConfigMockNM::freeConnectionArrElement(gpointer connection, gpointer userData)
{
	g_object_unref((GObject*)connection);
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

void ConfigMockNM::setActiveConnectionState(NMActiveConnectionState state)
{
	if (nm_active_connection_get_state(activeConnection) != state)
	{
		g_object_set((GObject*)activeConnection, NM_ACTIVE_CONNECTION_STATE, NM_ACTIVE_CONNECTION_STATE_ACTIVATING, NULL);
		g_signal_emit_by_name(activeConnection, "notify::" NM_ACTIVE_CONNECTION_STATE);
	}
}

void ConfigMockNM::resetActiveConnectionState()
{
	g_object_set((GObject*)activeConnection, NM_ACTIVE_CONNECTION_STATE, NM_ACTIVE_CONNECTION_STATE_UNKNOWN, NULL);
}

GPtrArray* ConfigMockNM::getDevices()
{
	return devices;
}

void ConfigMockNM::addDevices(NMDevice* deviceToAdd, int count)
{
	NMDevice* device = deviceToAdd;
	for (int i = 0; i < count; i++)
		g_ptr_array_add(devices, device);
}

void ConfigMockNM::addNonWifiDevices(int count)
{
	addDevices(MOCK_VALID_NONWIFI_DEVICE, count);
}

void ConfigMockNM::addWifiDevices(int count)
{
	addDevices(MOCK_VALID_WIFI_DEVICE, count);
}

void ConfigMockNM::resetArrayContents(GPtrArray** arr)
{
	g_ptr_array_unref(*arr);
	*arr = g_ptr_array_new();
}

void ConfigMockNM::resetDeviceArrayContents()
{
	resetArrayContents(&devices);
}

GPtrArray* ConfigMockNM::getConnections()
{
	return connections;
}

void ConfigMockNM::addConnection(NMConnection* connection)
{
	g_ptr_array_add(connections, connection);
}

void ConfigMockNM::resetConnectionArrayContents(bool freeInternals)
{
	if (freeInternals)
		g_ptr_array_foreach(connections, (GFunc)freeConnection, NULL);
	resetArrayContents(&connections);
}

ConfigMockNM::ConfigMockNM()
{
	client = MOCK_INVALID_CLIENT;
	connectivityState = NM_CONNECTIVITY_NONE;
	devices = g_ptr_array_new();
	connections = g_ptr_array_new();
	activeConnection = (NMActiveConnecton*)g_object_new(NM_TYPE_ACTIVE_CONNECTION, NM_ACTIVE_CONNECTION_STATE, NM_ACTIVE_CONNECTION_STATE_UNKNOWN, NULL);
}

ConfigMockNM::~ConfigMockNM()
{
	g_ptr_array_unref(devices);
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
