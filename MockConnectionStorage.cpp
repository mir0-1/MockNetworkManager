#include "MockConnectionStorage.h"

GPtrArray* MockConnectionStorage::getConnections() const
{
	return connections;
}

void MockConnectionStorage::addConnection(NMConnection* connection)
{
	g_ptr_array_add(connections, (gpointer)connection);
}

bool MockConnectionStorage::removeConnection(NMConnection* connection)
{
	return (bool)g_ptr_array_remove(connections, (gpointer)connection);
}

void MockConnectionStorage::freeConnections(bool reinit, bool freeInternals)
{
	if (freeInternals)
		for (int i = 0; i < connections->len; i++)
			g_object_unref((GObject*)connections->pdata[i]);

	g_ptr_array_unref(connections);

	if (reinit)
		connections = g_ptr_array_new();
}

NMActiveConnection* MockConnectionStorage::activateConnection(NMConnection* connection)
{
	deactivateConnection();

	if (!g_ptr_array_find(connections, (gpointer)connection, NULL))
		return NULL;

	activeConnection = (NMActiveConnection*)connection;
	activeConnectionState = NM_ACTIVE_CONNECTION_STATE_ACTIVATED;

	return activeConnection;
}

void MockConnectionStorage::deactivateConnection()
{
	activeConnection = NULL;
	activeConnectionState = NM_ACTIVE_CONNECTION_STATE_UNKNOWN;
}

NMActiveConnectionState MockConnectionStorage::getActiveConnectionState() const
{
	return activeConnectionState;
}

NMConnectivityState MockConnectionStorage::getConnectivityState() const
{
	return connectivityState;
}

void MockConnectionStorage::setConnectivityState(NMConnectivityState newState)
{
	connectivityState = newState;
}

MockConnectionStorage::MockConnectionStorage()
{
	connections = g_ptr_array_new();
	deactivateConnection();
}

~MockConnectionStorage::MockConnectionStorage()
{
	deactivateConnection();
	freeConnections(false, true);
}
