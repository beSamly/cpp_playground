#include "PlayerManager.h"

int count = 0;

void PlayerManager::AddPlayer()
{
	WRITE_LOCK;
	playerIds.push_back(count++);
}

void PlayerManager::ReadAllPlayer()
{
	READ_LOCK;
	auto size = playerIds.size();
	std::cout << "vector size is " << size << std::endl;
}
