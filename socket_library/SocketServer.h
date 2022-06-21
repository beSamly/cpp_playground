#pragma once
#include <functional>
#include "./Network/BaseSocketServer.h"

using SessionFactory = std::function<SessionRef(void)>;

class SocketServer : public BaseSocketServer
{
public:
	SocketServer(NetAddress netAddress, int32 maxSessionCount) : BaseSocketServer(maxSessionCount, netAddress) {
	};

private :
	SessionFactory _sessionFactory;
public:
	bool Start();
	void Close();

protected:
	// Inherited via BaseSocketServer
	SessionRef CreateSession() override;
};


 