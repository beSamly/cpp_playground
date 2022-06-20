#include "PacketHandler.h"

unsigned char* PacketHandler::protoToBuffer(Protocol::Player& player_proto)
{
	return _protoToBuffer<Protocol::Player>(player_proto, 1);
}
