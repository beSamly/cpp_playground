#include <thread>
#include <vector>
#include <chrono>

#include "SocketServer.h"
#include "Global.h"
#include "Network/Session.h"
#include "Network/SendBuffer.h"

int main() {
	SocketServerRef socketServer = MakeShared<SocketServer>(NetAddress(L"127.0.0.1", 7777), 100);
	//SocketServer* socketServer = new SocketServer(NetAddress(L"127.0.0.1", 7777), 100);
	socketServer->Start();
	std::vector<thread>	_threads;
	for (int32 i = 0; i < 5; i++)
	{
		_threads.push_back(thread([=]()
		{
			while (true)
			{
				socketServer->GetIocpCore()->HandleIocpEvent();
			}
		}));
	}

	// 패킷 보내기 테스트
	_threads.push_back(thread([=]()
	{
		while (true)
		{
			//sleep_for(std::chrono::milliseconds(10000));
			for (auto& session : socketServer->_sessions) {
				char s [] = "what the fuck";
				BYTE* message = new BYTE[4096];
				std::memcpy(&message[0], s, sizeof s);
				SendBufferRef sendBuffer = MakeShared<SendBuffer>(message, sizeof(s));
				sendBuffer->Close(sizeof(s));
				session->Send(sendBuffer);
			}
			sleep_for(std::chrono::milliseconds(2000));
		}
	}));

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