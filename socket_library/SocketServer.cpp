#include "SocketServer.h"
#include "Global.h"
#include <functional>
#include "Network/Session.h"
#include "ClientSession.h"

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

void SocketServer::AddSession(SessionRef session)
{
	WRITE_LOCK;
	_sessionCount++;
	_sessions.insert(session);
}

void SocketServer::ReleaseSession(SessionRef session)
{
	WRITE_LOCK;
	ASSERT_CRASH(_sessions.erase(session) != 0);
	_sessionCount--;
}

/*---------------------
	 인터페이스 구현
----------------------*/
SessionRef SocketServer::CreateSession()
{
	auto session = MakeShared<ClientSession>();
	
	session->SetOwner(std::static_pointer_cast<BaseSocketServer>(shared_from_this()));

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return std::static_pointer_cast<Session>(session);
}

// BaseSocketServer에서 ProcessAccept() 호출 시에 이벤트 발생
void SocketServer::OnConnected(SessionRef session)
{
	AddSession(session);
}

// Session 에서 ProcessDisconnect() 호출 시에 이벤트 발생
void SocketServer::OnDisconnected(SessionRef session)
{
	ReleaseSession(session);
}