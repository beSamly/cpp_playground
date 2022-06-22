#include "../Global.h"
#include "BaseSocketServer.h"
#include "SocketUtils.h"
#include "IocpEvent.h"
#include "Session.h"

/*--------------
	BaseSocketServer
---------------*/

BaseSocketServer::~BaseSocketServer()
{
	SocketUtils::Close(_socket);

	for (AcceptEvent* acceptEvent : _acceptEvents)
	{
		// TODO

		delete(acceptEvent);
	}
}

IocpCoreRef BaseSocketServer::GetIocpCore()
{
	return _iocpCore;
}

bool BaseSocketServer::StartAccept()
{
	// 소켓 초기화 및 ConnectEx, DisconnectEx, AcceptEx 함수 주소 바인딩
	SocketUtils::Init();

	// 서버 소켓 생성
	_socket = SocketUtils::CreateSocket();
	if (_socket == INVALID_SOCKET)
		return false;

	// IOCP 포트에 서버 소켓 등록
	if (_iocpCore->Register(shared_from_this()) == false)
		return false;

	// 옵션 세팅
	if (SocketUtils::SetReuseAddress(_socket, true) == false)
		return false;

	if (SocketUtils::SetLinger(_socket, 0, 0) == false)
		return false;

	// 소켓을 netAddress 에 바인딩
	if (SocketUtils::Bind(_socket, _netAddress) == false)
		return false;

	// Listen 시작
	if (SocketUtils::Listen(_socket) == false)
		return false;

	const int32 acceptCount = _maxSessionCount;
	for (int32 i = 0; i < acceptCount; i++)
	{
		AcceptEvent* acceptEvent = new AcceptEvent();
		acceptEvent->owner = shared_from_this();
		_acceptEvents.push_back(acceptEvent);
		RegisterAccept(acceptEvent);
	}

	return true;
}

void BaseSocketServer::CloseSocket()
{
	SocketUtils::Close(_socket);
}

HANDLE BaseSocketServer::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void BaseSocketServer::HandleIocpEvent(IocpEvent* iocpEvent, int32 numOfBytes)
{
	ASSERT_CRASH(iocpEvent->eventType == EventType::Accept);
	AcceptEvent* acceptEvent = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(acceptEvent);
}

void BaseSocketServer::RegisterAccept(AcceptEvent* acceptEvent)
{
	SessionRef session = CreateSession(); // Register IOCP

	acceptEvent->Init();
	acceptEvent->session = session;

	DWORD bytesReceived = 0;
	if (false == SocketUtils::AcceptEx(_socket, session->GetSocket(), session->_recvBuffer.WritePos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, OUT & bytesReceived, static_cast<LPOVERLAPPED>(acceptEvent)))
	{
		const int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// 일단 다시 Accept 걸어준다
			RegisterAccept(acceptEvent);
		}
	}
}

void BaseSocketServer::ProcessAccept(AcceptEvent* acceptEvent)
{
	SessionRef session = acceptEvent->session;

	if (false == SocketUtils::SetUpdateAcceptSocket(session->GetSocket(), _socket))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	SOCKADDR_IN sockAddress;
	int32 sizeOfSockAddr = sizeof(sockAddress);
	if (SOCKET_ERROR == ::getpeername(session->GetSocket(), OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeOfSockAddr))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	session->SetNetAddress(NetAddress(sockAddress));
	session->ProcessConnect();

	// BaseSocketServer의 구현부에서 세션이 연결되어 생성되었을 때 실행할 함수 호출
	OnConnected(session);

	RegisterAccept(acceptEvent);
}