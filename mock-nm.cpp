#include "configMockNm.h"

#define ASYNC_PARAM_PATTERN GCancellable *cancellable, GAsyncReadyCallback callback, gpointer userData
#define FINISH_PARAM_PATTERN GAsyncResult *result, GError **error

static void setActiveConnectionState(gpointer state)
{
	NMActiveConnectionState activeConnectionState = (NMActiveConnectionState)(long)state;
	NMActiveConnection* activeConnection = configMockNM.getActiveConnection();
	if (nm_active_connection_get_state(activeConnection) != activeConnectionState)
	{
		g_object_set((GObject*)activeConnection, NM_ACTIVE_CONNECTION_STATE, activeConnectionState, NULL);
		g_signal_emit_by_name(activeConnection, "notify::" NM_ACTIVE_CONNECTION_STATE);
	}
}

void nm_client_new_async(ASYNC_PARAM_PATTERN)
{
	callback(NULL, NULL, userData);
}

NMClient* nm_client_new_finish(FINISH_PARAM_PATTERN)
{
	return configMockNM.getClient();
}

void nm_client_check_connectivity_async(NMClient *client, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)client, NULL, userData);
}

NMConnectivityState nm_client_check_connectivity_finish(NMClient* client, FINISH_PARAM_PATTERN)
{
	return configMockNM.getConnectivityState();
}

const GPtrArray* nm_client_get_devices(NMClient* client)
{
	return (const GPtrArray*)configMockNM.getDevices();
}

const GPtrArray* nm_client_get_connections(NMClient* client)
{
	return (const GPtrArray*)configMockNM.getConnections();
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
	NMConnection* connectionToCheck = (NMConnection*)result;
	if (result == NULL || client == NULL || !g_ptr_array_find(configMockNM.getConnections(), (NMConnection*)connectionToCheck, NULL))
		return NULL;
	NMActiveConnection* activeConnection = configMockNM.getActiveConnection();
	g_object_set(activeConnection, NM_ACTIVE_CONNECTION_CONNECTION, connectionToCheck, NULL);
	setActiveConnectionState((gpointer)NM_ACTIVE_CONNECTION_STATE_ACTIVATING);
	//g_timeout_add_once(3000, setActiveConnectionState, (gpointer)(configMockNM.getFailActivation() ? NM_ACTIVE_CONNECTION_STATE_UNKNOWN : NM_ACTIVE_CONNECTION_STATE_ACTIVATED));
	return activeConnection;
}

NMActiveConnection* nm_client_add_and_activate_connection_finish(NMClient* client, FINISH_PARAM_PATTERN)
{
	NMConnection* connection = (NMConnection*)result;
	if (connection == NULL)
		return NULL;
	configMockNM.addConnection(connection);
	return nm_client_activate_connection_finish(client, result, error);
}

void nm_remote_connection_delete_async(NMRemoteConnection* connection, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)connection, NULL, userData);
}

gboolean nm_remote_connection_delete_finish(NMRemoteConnection* connection, FINISH_PARAM_PATTERN)
{
	if (connection == NULL || !g_ptr_array_remove(configMockNM.getConnections(), (NMConnection*)connection))
		return false;
	
	return true;
}

const GPtrArray* nm_device_wifi_get_access_points(NMDeviceWifi* device)
{
	return configMockNM.getAccessPoints();
}
