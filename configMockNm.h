#pragma once
#include <NetworkManager.h>
#include <glib.h>

typedef struct
{
	ConfigMockNM* thisObjData;
	NMActiveConnectionState state;
} ActiveConnectionTransfer;

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
		ActiveConnectionTransfer activeConnectionTransfer;
	
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
		NMActiveConnection* getActiveConnection();
		GPtrArray* getAccessPoints();
		void addAccessPoint(NMAccessPoint* accessPoint);
		
		static void setActiveConnectionState(gpointer stateTransfer);
	
		ConfigMockNM();
		~ConfigMockNM();
	
} configMockNM;
