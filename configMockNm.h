#pragma once
#include <NetworkManager.h>
#include <glib.h>

#define MOCK_VALID_CLIENT 0x1
#define MOCK_INVALID_CLIENT 0x0
#define MOCK_VALID_NONWIFI_DEVICE 0x1
#define MOCK_VALID_WIFI_DEVICE 0x2

class ConfigMockNM
{
	private:
		NMClient* client;
		NMConnectivityState connectivityState;
		GPtrArray* devices;
		GPtrArray* connections;
		bool failActivation;
		NMActiveConnection* activeConnection;
	
		void addDevices(NMDevice* device, int count);
		void resetArrayContents(GPtrArray** arr);
		
		static void freeConnectionArrElement(gpointer connection, gpointer userData);
		
	public:
		NMClient* getClient();
		void setClientValid();
		void setClientInvalid();
		NMConnectivityState getConnectivityState();
		void resetActiveConnectionState();
		void setConnectivityState(NMConnectivityState newConnectivityState);
		GPtrArray* getDevices();
		void addNonWifiDevices(int count);
		void addWifiDevices(int count);
		void resetDeviceArrayContents();
		GPtrArray* getConnections();
		void addConnection(NMConnection* connection);
		void resetConnectionArrayContents(bool freeInternals);
		bool getFailActivation();
		void setFailActivation(bool value);
		
		static void setActiveConnectionState(NMActiveConnectionState state);
	
		ConfigMockNM();
		~ConfigMockNM();
	
} configMockNM;
