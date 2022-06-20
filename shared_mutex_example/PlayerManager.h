#pragma once
#include <vector>
#include <iostream>
#include "LockMacro.h"
#include "SharedMutexGuard.h"

using std::shared_mutex;
using std::vector;

class PlayerManager
{
private:
	USE_LOCK;
	vector<int> playerIds;

public:
	void ReadAllPlayer();
	void AddPlayer();
};

