#include "SocketServer.h"
#include "Global.h"
#include <functional>
#include "Network/Session.h"
#include "ClientSession.h"

SessionRef SocketServer::CreateSession()
{
	//auto a = make_shared<ClientSession>();
	//TODO ���⼭ ���� ���� �ִ�.static_pointer_cast ����ϴ°� �´��� ��Ȯ��...
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
