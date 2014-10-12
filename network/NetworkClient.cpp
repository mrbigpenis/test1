#include "stdafx.h"
#include "NetworkClient.h"


NetworkClient::NetworkClient()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	printf("NetworkClient has started\n\n");

	WSADATA wsaData;
	mainSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	errorCheck = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (errorCheck != 0) {
		printf("WSAStartup failed with error code: %d\n", errorCheck);
		exit(1);
	}

	// setting address info
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP; // Connection type is TCP

	// Check the address at the set port
	errorCheck = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);

	if (errorCheck != 0) {
		printf("couldnt getaddrinfo, error code: %d\n", errorCheck);
		WSACleanup();
		exit(1);
	}

	// try to connect until it works
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		mainSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (mainSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}

		// Connect to server.
		errorCheck = connect(mainSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (errorCheck == SOCKET_ERROR)
		{
			closesocket(mainSocket);
			mainSocket = INVALID_SOCKET;
			printf("could not connect to ip \n");
		}
	}

	freeaddrinfo(result);

	if (mainSocket == INVALID_SOCKET)
	{
		printf("unable to connect to server\n");
		WSACleanup();
	}
}


NetworkClient::~NetworkClient()
{
}
