#pragma once
#include "../Global.h"

/*----------------
	IocpObject
-----------------*/

class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void HandleIocpEvent(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

/*--------------
	IocpCore
---------------*/

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

public:
	HANDLE		GetHandle() { return _iocpHandle; }
	bool		Register(IocpObjectRef iocpObject);
	bool		HandleIocpEvent(uint32 timeoutMs = INFINITE);

private:
	HANDLE		_iocpHandle;
};