#pragma once
#include <NetworkManager.h>
#include <glib.h>

class MockConnectionStorage
{
	private:
		GPtrArray* connections;
		NMActiveConnection* activeConnection;
		NMActiveConnectionState activeConnectionState;
		NMConnectivityState connectivityState;

	public:
		GPtrArray* getConnections() const;
		void addConnection(NMConnection* connection);
		bool removeConnection(NMConnection* connection);
		void freeConnections(bool reinit, bool freeInternals);
		NMActiveConnection* activateConnection(NMConnection* connection);
		void deactivateConnection();
		NMActiveConnectionState getActiveConnectionState() const;
		NMConnectivityState getConnectivityState() const;
		void setConnectivityState(NMConnectivityState newState);

		MockConnectionStorage();
		~MockConnectionStorage();
};
