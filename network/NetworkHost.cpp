#include "stdafx.h"
#include "NetworkHost.h"

unsigned int NetworkHost::client_id = 0;

NetworkHost::NetworkHost()
{
	
	// create WSADATA object
	WSADATA wsaData;

	// sockets for the server
	listenSocket = INVALID_SOCKET;
	clientSocket = INVALID_SOCKET;


	// address info for the server to listen to
	struct addrinfo *addr_result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		printf("WSAStartup failed with error: %d\n", result);
		exit(1);
	}

	// set address information
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;    // TCP connection
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port, does not need address since its a local server
	result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &addr_result);

	if (result != 0) {
		printf("getaddrinfo failed with error: %d\n", result);
		WSACleanup();
		exit(1);
	}

	// Create a SOCKET for connecting to server
	listenSocket = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);

	if (listenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(addr_result);
		WSACleanup();
		exit(1);
	}

	// Set the mode of the socket to be nonblocking
	u_long sMode = 1;
	result = ioctlsocket(listenSocket, FIONBIO, &sMode);

	if (result == SOCKET_ERROR) {
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		exit(1);
	}

	// Setup the TCP listening socket
	result = bind(listenSocket, addr_result->ai_addr, (int)addr_result->ai_addrlen);

	if (result == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(addr_result);
		closesocket(listenSocket);
		WSACleanup();
		exit(1);
	}

	// no longer need address information
	freeaddrinfo(addr_result);

	// start listening for new clients attempting to connect
	result = listen(listenSocket, SOMAXCONN);

	if (result == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		exit(1);
	}

	// at this point, the main socket for the server is set up and listening on DEFAULT_PORT.
}


// accept new connections
bool NetworkHost::acceptNewClient(unsigned int & id)
{
	// if client waiting, accept the connection and save the socket
	clientSocket = accept(listenSocket, NULL, NULL);

	if (clientSocket != INVALID_SOCKET)
	{
		//disable nagle on the client's socket
		char value = 1;
		setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

		// insert new client into session id table
		sockaddr client_info = { 0 };
		int addr_len = sizeof(client_info);

		sessions.insert(std::pair<unsigned int, SOCKET>(id, clientSocket));
		result = getpeername(clientSocket, &client_info, &addr_len);

		struct sockaddr_in *client_in_addr = (struct sockaddr_in *)&client_info;
		char *client_ip_addr = inet_ntoa(client_in_addr->sin_addr);
		printf("Connected with %s", client_ip_addr);
		client_ip.push_back(client_ip_addr);

		return true;
	}

	return false;
}

void NetworkHost::update() {

	if (acceptNewClient(client_id)) {
		printf("\nNew Client (ID %d) has connected.\ntest1server >> ", client_id);
		client_id++;
	}
	receiveFromClients();
}

int NetworkHost::receiveData(unsigned int client_id, char * recvbuf) {
	if (sessions.find(client_id) != sessions.end()) {
		SOCKET curSocket = sessions[client_id];
		result = network::receiveMessage(curSocket, recvbuf, MAX_PACKET_SIZE);
		if (result == 0) {
			printf("\nConnection (ID %d) closed.\ntest1server >> ");
			closesocket(curSocket);
		}
		return result;
	}

	return 0;
}

void NetworkHost::receiveFromClients() {
	Packet packet;

	// Iterate through all clients with an iterator object for maps
	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = sessions.begin(); iter != sessions.end(); iter++)
	{
		int data_length = receiveData(iter->first, server_data);

		if (data_length <= 0) {
			// no data
			continue;
		}

		int i = 0;
		while (i < (unsigned int)data_length) {
			packet.deserialize(&(server_data[i]));
			i += sizeof(Packet);

			switch (packet.type) {
			case ACTION_INIT:
				printf("\nReceived init package!\ntest1server >> ");
				break;
			default:
				printf("\nPackage type not recognized.\ntest1server >> ");
				break;
			}
		}

	}


}


NetworkHost::~NetworkHost()
{
}
