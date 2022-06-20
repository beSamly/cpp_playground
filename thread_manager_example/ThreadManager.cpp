#include "ThreadManager.h"

/*------------------
	ThreadManager
-------------------*/

thread_local unsigned __int32	LThreadId = 0;

ThreadManager::ThreadManager()
{
	// Main Thread
	InitTLS();
}

using LockGuard = std::lock_guard<std::mutex>;

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Start(function<void(unsigned __int32 LThreadId)> callback)
{
	LockGuard guard(_lock);

	_threads.push_back(thread([=]()
	{
		InitTLS();
		callback(LThreadId);
		DestroyTLS();
	}));
}

void ThreadManager::Join()
{
	for (thread& t : _threads)
	{
		if (t.joinable())
			t.join();
	}
	_threads.clear();
}

void ThreadManager::InitTLS()
{
	static atomic<unsigned __int32> SThreadId = 1;
	LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}

//void ThreadManager::DoGlobalQueueWork()
//{
//	while (true)
//	{
//		uint64 now = ::GetTickCount64();
//		if (now > LEndTickCount)
//			break;
//
//		JobQueueRef jobQueue = GGlobalQueue->Pop();
//		if (jobQueue == nullptr)
//			break;
//
//		jobQueue->Execute();
//	}
//}
//
//void ThreadManager::DistributeReservedJobs()
//{
//	const uint64 now = ::GetTickCount64();
//
//	GJobTimer->Distribute(now);
//}
