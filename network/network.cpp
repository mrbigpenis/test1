// network.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "network.h"



using namespace std;

int network::sendMessage(SOCKET curSocket, char * message, int messageSize) {

	OutputDebugString(L"sent message: ");
	OutputDebugStringA(message);
	OutputDebugString(L"\n");
	return send(curSocket, message, messageSize, 0);
}

int network::receiveMessage(SOCKET curSocket, char * buffer, int bufSize) {

	OutputDebugString(L"received message: ");
	OutputDebugStringA(buffer);
	OutputDebugString(L"\n");
	return recv(curSocket, buffer, bufSize, 0);
}



