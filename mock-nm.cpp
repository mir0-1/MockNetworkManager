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

NMActiveConnection* nm_client_activate_connection_finish(NMClient *client, FINISH_PARAM_PATTERN)
{
	NMConnection* connectionToCheck = result;
	if (!g_ptr_array_find(connections, (NMConnection*)connectionToCheck))
		return NULL;
	configMockNM.setActiveConnectionState(NM_ACTIVE_CONNECTION_STATE_ACTIVATING);
	g_timeout_add_once(3000, ConfigMockNM::setActiveConnectionState, (gpointer)(configMockNM.getFailActivation() ? NM_ACTIVE_CONNECTION_STATE_UNKNOWN : NM_ACTIVE_CONNECTION_STATE_ACTIVATED));
}
