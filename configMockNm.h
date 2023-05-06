#pragma once
#include <NetworkManager.h>
#include <glib.h>

#define MOCK_VALID_CLIENT 0x1
#define MOCK_INVALID_CLIENT 0x0

class ConfigMockNM
{
	private:
		NMClient* client;
		NMConnectivityState connectivityState;
		GPtrArray* devices;
		GPtrArray* connections;
		GPtrArray* accessPoints;
		bool failActivation;
		NMActiveConnection* activeConnection;
		
		static void freeArrElement(gpointer element, gpointer userData);
		
	public:
		NMClient* getClient();
		void setClientValid();
		void setClientInvalid();
		NMConnectivityState getConnectivityState();
		void resetActiveConnectionState();
		void setConnectivityState(NMConnectivityState newConnectivityState);
		GPtrArray* getDevices();
		void addDevice(NMDevice* device);
		GPtrArray* getConnections();
		void addConnection(NMConnection* connection);
		bool getFailActivation();
		void setFailActivation(bool value);
		NMActiveConnection* getActiveConnection();
		GPtrArray* getAccessPoints();
		void addAccessPoint(NMAccessPoint* accessPoint);
		void resetArrayContents(GPtrArray** arr, bool freeInternals, bool reinit);
	
		ConfigMockNM();
		~ConfigMockNM();
	
};
