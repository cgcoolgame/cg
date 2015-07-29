
#ifndef cgSocket_h__
#define cgSocket_h__
#include <string>
#include <windows.h>
using std::string;

// 套接字的监听器
class cgSocketListener
{
public:
	// 创建和销毁
	virtual void OnCreate(int nID, int nError){}
	virtual void OnClose(int nID, int nError){}

	// 连接和断连
	virtual void OnConnect(int nID, int nError){}
	virtual void OnDisconnect(int nID, int nError){}

	// 收发数据
	virtual void OnSend(int nID, int nError){}
	virtual void OnReceive(int nID, int nError){}

	// 用于服务器：收到连接
	virtual void OnAccept(int nID, int nError){}
};

// 客户端用的套接字
class cgSocket
{
public:
	cgSocket(void);
	~cgSocket(void);

	// 创建和销毁
	virtual bool CreateSocket(unsigned uPort, LPCTSTR lpctAddr) = NULL;
	virtual void CloseSocket() = NULL;

	// 连接:客户端用
	virtual bool ConnectServer(LPCTSTR lpctAddr, unsigned uPort){return true;}

	// 监听：用于服务器
	virtual bool ListenConnection(int nNum = 5){return true;}
	virtual cgSocket* AcceptConnection(){return NULL;}

	// 收发数据
	virtual int SendData(void * pBuff, int nBuffLen) = NULL;
	virtual int ReceiveData(void * pBuff, int nBuffLen) = NULL;

	void SetListener(cgSocketListener * pkListener);

	void SetID(int nID);
	int GetID();

protected:
	cgSocketListener * m_pkListener;
	int m_nID;
};

#endif // cgSocket_h__
