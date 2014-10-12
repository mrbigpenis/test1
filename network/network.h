#define NETWORK_API __declspec(dllexport)

#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <vector>
#include "NetworkData.h"

class network
	{
	public:

		NETWORK_API static int sendMessage(SOCKET curSocket, char * message, int messageSize);
		NETWORK_API static int receiveMessage(SOCKET curSocket, char * buffer, int bufSize);

	private:
};
