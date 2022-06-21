#include "SocketServer.h"
#include "Global.h"
#include <thread>
#include <vector>

int main() {
	SocketServer* socketServer = new SocketServer(NetAddress(L"127.0.0.1", 7777), 100);
	socketServer->Start();

	std::vector<thread>	_threads;
	for (int32 i = 0; i < 5; i++)
	{
		_threads.push_back(thread([=]()
		{
		}));
	}

	for (thread& t : _threads)
	{
		if (t.joinable())
			t.join();
	}

	//// Main Thread
	//DoWorkerJob(service);

	//GThreadManager->Join();
	return 0;
}