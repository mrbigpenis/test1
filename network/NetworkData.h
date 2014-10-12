#pragma once

#include <string.h>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {

	ACTION_INIT = 0,
	ACTION_EVENT = 1

};


struct Packet{

	unsigned int type;

	void serialize(char* data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char* data) {
		memcpy(this, data, sizeof(Packet));
	}
};