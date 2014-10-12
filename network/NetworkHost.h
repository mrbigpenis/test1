#pragma once

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1337" 

#include <winsock2.h>
#include <Windows.h>
#include "network.h"
#include <ws2tcpip.h>
#include <map>

#pragma comment (lib, "Ws2_32.lib")

class NETWORK_API NetworkHost
{
public:
	NetworkHost();
	~NetworkHost();

	// Socket to listen for new connections
	SOCKET listenSocket;

	// Socket to give to the clients
	SOCKET clientSocket;

	// for error checking return values
	int result;

	static unsigned int client_id;

	bool acceptNewClient(unsigned int &id);
	void update();
	int receiveData(unsigned int client_id, char * recvbuf);
	void receiveFromClients();

	// table to keep track of each client's socket
	std::map<unsigned int, SOCKET> sessions;
	std::vector<char *> client_ip;
	char server_data[MAX_PACKET_SIZE];
	
private:

};

