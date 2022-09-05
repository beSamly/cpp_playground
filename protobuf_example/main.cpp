#include <iostream>
#include "protobuf/Player.pb.h"
#include "protobuf/EquipItem.pb.h"
#include "protobuf/SearchRequest.pb.h"
#include "PacketHandler.h"

#ifdef _DEBUG
#pragma comment(lib,"Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib,"Protobuf\\Debug\\libprotobuf.lib")
#endif

void onPacketArrive(unsigned char* buffer) {
	auto packetHeader = reinterpret_cast<PacketHeader*>(buffer);
	auto packetSize = packetHeader->packetSize;
	auto packetId = packetHeader->packetId;
	auto packetHeaderSize = sizeof(PacketHeader);
	auto dataSize = packetSize - packetHeaderSize;

	std::cout << "Packet Id : " << packetId << " PacketSzie : " << packetSize << std::endl;

	if (packetHeader->packetId == 1) {
		std::cout << "Got Player packet" << std::endl;

		Protocol::Player player;
		player.ParseFromArray(buffer + packetHeaderSize, dataSize);

		std::cout << "[Got player] AccountId " << player.accountid() << " Username : " << player.username() << std::endl;
		for (auto& equipItem : player.equipitems())
		{
			std::cout << "equipitemindex : " << equipItem.equipitemindex() << " slotindex : " << equipItem.slotindex() << std::endl;
		}
	}
	else {
		std::cout << "Got unregistered packet";
	}
}

class MyTest {
public:
	int itemIndex;
	int equipItemSlot;

public:
	int add() {
		return itemIndex + equipItemSlot;
	}

	int sub() {
		return itemIndex - equipItemSlot;
	}
};

int main()
{
	auto sizeOfMyTest = sizeof(MyTest);
	MyTest t1;
	auto sizeOft1 = sizeof(t1);
	auto sizeOfInt = sizeof(t1.itemIndex);

	Protocol::Player player;
	Protocol::SearchRequest s1;

	player.set_accountid(1256);
	player.set_username("Samuel Lee");

	auto item1 = player.add_equipitems();
	item1->set_equipitemindex(1001);
	item1->set_slotindex(1);

	auto item2 = player.add_equipitems();
	item2->set_equipitemindex(2002);
	item2->set_slotindex(2);

	auto item3 = player.add_equipitems();
	item3->set_equipitemindex(3001);
	item3->set_slotindex(3);

	auto buffer = PacketHandler::protoToBuffer(player);
	onPacketArrive(buffer);

	auto asd = sizeof(player);
	auto sdf = sizeof(*item1);


	//Protocol::Player player;
	std::cout << "Hello World!\n";
}

