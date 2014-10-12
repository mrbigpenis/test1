#pragma once

#define DEFAULT_BUFLEN 512

// yeee buddy
#define DEFAULT_PORT "1337"

#include <winsock2.h>
#include <Windows.h>
#include "network.h"
#include <ws2tcpip.h>
#include <stdio.h> 

// winsock libraries
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


class NetworkClient
{
public:

	int errorCheck;

	SOCKET mainSocket;




	NETWORK_API NetworkClient();
	NETWORK_API ~NetworkClient();
};

