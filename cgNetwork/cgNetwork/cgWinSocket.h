
#ifndef cgWinSocket_h__
#define cgWinSocket_h__
#include <afxsock.h>
#include "cgSocket.h"

class cgWinSocket:
	public CAsyncSocket,
	public cgSocket
{
public:
	cgWinSocket(void);
	~cgWinSocket(void);

	// Overridable callbacks
protected:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);

public:
	// 创建和销毁
	virtual bool CreateSocket( unsigned uPort = 0, LPCTSTR lpctAddr = NULL);
	virtual void CloseSocket();

	// 连接
	virtual bool ConnectServer(LPCTSTR lpctAddr, unsigned uPort);

	// 监听：用于服务器
	virtual bool ListenConnection(int nNum = 5);
	virtual cgSocket* AcceptConnection();

	// 收发数据
	virtual int SendData(void * pBuff, int nBuffLen);
	virtual int ReceiveData(void * pBuff, int nBuffLen);

	// 
};

#endif // cgWinSocket_h__
