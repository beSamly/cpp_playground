#pragma once

#include <functional>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>

using std::mutex;
using std::vector;
using std::thread;
using std::function;
using std::atomic;

/*------------------
	ThreadManager
-------------------*/

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void	Start(function<void(unsigned __int32 LThreadId)> callback);
	void	Join();

	static void InitTLS();
	static void DestroyTLS();

private:
	std::mutex			_lock;
	vector<thread>	_threads;
};

