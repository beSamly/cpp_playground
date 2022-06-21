#include "Global.h"
#include "Network/Session.h"
/*-----------------
	ClientSession
------------------*/

struct PacketHeader
{
	uint16 size;
	uint16 id; // ��������ID (ex. 1=�α���, 2=�̵���û)
};

class ClientSession : public Session
{
public:
	ClientSession();
	virtual ~ClientSession();

	ClientSessionRef	GetClientSessionRef() { return std::static_pointer_cast<ClientSession>(shared_from_this()); }

private:
	/* �������̽� ���� */
	virtual void	OnConnected() override;
	virtual void	OnDisconnected() override;
	virtual void	OnSend(int32 len) override;
	virtual int32	OnRecv(BYTE* buffer, int32 len) override;

private:
	void			OnRecvPacket(BYTE* buffer, int32 len);

protected:
};