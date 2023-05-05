#include "configMockNM.h"

#define ASYNC_PARAM_PATTERN GCancellable *cancellable, GAsyncReadyCallback callback, gpointer userData
#define FINISH_PARAM_PATTERN GAsyncResult *result, GError **error

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
	callback((GObject*)client, connection, userData);
}

void nm_client_add_and_activate_connection_async(NMClient *client, NMConnection *connection, NMDevice *device, const char *specific_object, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)client, connection, userData);
}

NMActiveConnection* nm_client_activate_connection_finish(NMClient *client, FINISH_PARAM_PATTERN)
{
	NMConnection* connectionToCheck = result;
	if (!g_ptr_array_find(configMockNM.getConnections(), (NMConnection*)connectionToCheck))
		return NULL;
	configMockNM.setActiveConnectionState(NM_ACTIVE_CONNECTION_STATE_ACTIVATING);
	g_timeout_add_once(3000, ConfigMockNM::setActiveConnectionState, (gpointer)(configMockNM.getFailActivation() ? NM_ACTIVE_CONNECTION_STATE_UNKNOWN : NM_ACTIVE_CONNECTION_STATE_ACTIVATED));
}

NMActiveConnection* nm_client_add_and_activate_connection_finish(NMClient* client, FINISH_PARAM_PATTERN)
{
	configMockNM.addConnection((NMConnection*)result);
	return nm_client_activate_connection_finish(client, result, error);
}

void nm_remote_connection_delete_async(NMRemoteConnection* connection, ASYNC_PARAM_PATTERN)
{
	callback((GObject*)connection, NULL, userData);
}

gboolean nm_remote_connection_delete_finish(NMRemoteConnection* connection, FINISH_PARAM_PATTERN)
{
	if (!g_ptr_array_remove(configMockNM.getConnections(), (NMConnection*)connection))
		return false;
	
	return true;
}
