#include "MockClient.h"

#define ASYNC_PARAM_PATTERN GCancellable *cancellable, GAsyncReadyCallback callback, gpointer userData
#define FINISH_PARAM_PATTERN GAsyncResult *result, GError **error

MockClient mockClient;

void nm_client_new_async(ASYNC_PARAM_PATTERN)
{
	callback(NULL, NULL, userData);
}

NMClient* nm_client_new_finish(FINISH_PARAM_PATTERN)
{
	return mockClient.getClient();
}

void nm_client_check_connectivity_async(NMClient *client, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)client, NULL, userData);
}

NMConnectivityState nm_client_check_connectivity_finish(NMClient* client, FINISH_PARAM_PATTERN)
{
	return mockClient.getConnectionStorage().getConnectivityState();
}

const GPtrArray* nm_client_get_devices(NMClient* client)
{
	return (const GPtrArray*)mockClient.getDeviceStorage().getDevices();
}

const GPtrArray* nm_client_get_connections(NMClient* client)
{
	return (const GPtrArray*)mockClient.getConnectionStorage().getConnections();
}

void nm_client_activate_connection_async(NMClient *client, NMConnection *connection, NMDevice *device, const char *specific_object, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)client, (GAsyncResult*)connection, userData);
}

void nm_client_add_and_activate_connection_async(NMClient *client, NMConnection *connection, NMDevice *device, const char *specific_object, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)client, (GAsyncResult*)connection, userData);
}

NMActiveConnection* nm_client_activate_connection_finish(NMClient *client, FINISH_PARAM_PATTERN)
{
	mockClient.getConnectionStorage().activateConnection((NMConnection*)result);
}

NMActiveConnection* nm_client_add_and_activate_connection_finish(NMClient* client, FINISH_PARAM_PATTERN)
{
	NMConnection* connection = (NMConnection*)result;
	mockClient.getConnectionStorage().addConnection(connection);
	return nm_client_activate_connection_finish(client, result, error);
}

void nm_remote_connection_delete_async(NMRemoteConnection* connection, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)connection, NULL, userData);
}

gboolean nm_remote_connection_delete_finish(NMRemoteConnection* connection, FINISH_PARAM_PATTERN)
{
	return (gboolean)mockClient.getConnectionStorage().removeConnection((NMConnection*)connection);
}

const GPtrArray* nm_device_wifi_get_access_points(NMDeviceWifi* device)
{
	MockWifiDevice* mockWifiDevice = (MockWifiDevice*)device;
	return (const GPtrArray*)mockWifiDevice->getAccessPoints();
}

NMActiveConnectionState nm_active_connection_get_state(NMActiveConnection* activeConnection)
{
	NMActiveConnection* actualActiveConnection = mockClient.getConnectionStorage().getActiveConnection();
	if (activeConnection != actualActiveConnection)
		return NM_ACTIVE_CONNECTION_STATE_UNKNOWN;

	return mockClient.getConnectionStorage().getActiveConnectionState();
}
