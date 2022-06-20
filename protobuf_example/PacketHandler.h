#pragma once
#include "protobuf/Player.pb.h"

class PacketHeader {
public:
	unsigned __int16 packetSize;
	unsigned __int16 packetId;
};

class PacketHandler
{
public:
	static unsigned char* protoToBuffer(Protocol::Player &player_proto);
};

template<typename T>
unsigned char* _protoToBuffer(T& t, unsigned __int16 packetId)
{
	const unsigned __int16 dataSize = static_cast<unsigned __int16>(t.ByteSizeLong());
	const unsigned __int16 packetSize = dataSize + sizeof(PacketHeader);

	unsigned char* buffer = new unsigned char[1024];

	auto packetHeader = reinterpret_cast<PacketHeader*>(buffer);
	packetHeader->packetId = packetId;
	packetHeader->packetSize = packetSize;

	bool result = t.SerializeToArray(&packetHeader[1], dataSize);
	if (!result) {
		return nullptr;
	}

	return buffer;
}

