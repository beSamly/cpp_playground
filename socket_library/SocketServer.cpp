#include "SocketServer.h"
#include "Global.h"
#include <functional>
#include "Network/Session.h"
#include "ClientSession.h"

SessionRef SocketServer::CreateSession()
{
	//auto a = make_shared<ClientSession>();
	//TODO 여기서 터질 수도 있다.static_pointer_cast 사용하는게 맞는지 불확실...
	//return std::static_pointer_cast<Session>(a);
	//auto temp_ret = make_shared<Session>();
	return nullptr;
}

bool SocketServer::Start()
{
	if (StartAccept() == false)
		return false;

	return true;
}

void SocketServer::Close()
{
	// TODO
	CloseSocket();
}
