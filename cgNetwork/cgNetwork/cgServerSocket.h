#ifndef cgServerSocket_h__
#define cgServerSocket_h__

#include <afxsock.h>
#include "cgWinSocket.h"

class cgServerSocket:
	public CAsyncSocket
{
public:
	cgServerSocket(void);
	~cgServerSocket(void);

	virtual bool Initialize(LPCTSTR lpctSvrAddr, UINT uBindPort);

protected:
	virtual void OnAccept(int nErrorCode);

protected:
	cgWinSocket m_kConnectSocket;
};

#endif // cgServerSocket_h__
