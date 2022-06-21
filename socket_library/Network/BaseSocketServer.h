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

protected:
	/* derived class 에서 사용 */
	bool StartAccept();
	void CloseSocket();

protected:
	/* 인터페이스 구현 */
	virtual HANDLE GetHandle() sealed;
	virtual void HandleIocpEvent(class IocpEvent* iocpEvent, int32 numOfBytes = 0) sealed;

protected:
	/* 인터페이스 */
	virtual SessionRef CreateSession() abstract;

private:
	/* 수신 관련 */
	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);


protected:
	SOCKET _socket = INVALID_SOCKET;
	Vector<AcceptEvent*> _acceptEvents;
	int32 _maxSessionCount;
	NetAddress _netAddress;
	IocpCoreRef _iocpCore;
};

