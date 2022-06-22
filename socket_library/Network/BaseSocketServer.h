#pragma once
#include "IocpCore.h"
#include "NetAddress.h"

class AcceptEvent;
class ServerService;

/*--------------
	BaseSocketServer
---------------*/

class BaseSocketServer : public IocpObject
{
public:
	BaseSocketServer(int32 maxSessionCount, NetAddress netAddress) : _maxSessionCount(maxSessionCount), _netAddress(netAddress) {
		_iocpCore = make_shared<IocpCore>();
	};
	~BaseSocketServer();

public:
	IocpCoreRef GetIocpCore();

protected:
	/* derived class 에서 사용 */
	bool StartAccept();
	void CloseSocket();

protected:
	/* 인터페이스 구현 */
	virtual HANDLE GetHandle() sealed;
	virtual void HandleIocpEvent(class IocpEvent* iocpEvent, int32 numOfBytes = 0) sealed;



private:
	/* 수신 관련 */
	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);
	
	/* 인터페이스 */
protected:
	virtual SessionRef CreateSession() abstract;
public:
	virtual void OnConnected(SessionRef session) abstract;
	virtual void OnDisconnected(SessionRef session) abstract;

protected:
	SOCKET _socket = INVALID_SOCKET;
	Vector<AcceptEvent*> _acceptEvents;
	int32 _maxSessionCount;
	NetAddress _netAddress;
	IocpCoreRef _iocpCore;
};

