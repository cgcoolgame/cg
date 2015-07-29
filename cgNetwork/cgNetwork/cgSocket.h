
#ifndef cgSocket_h__
#define cgSocket_h__
#include <string>
#include <windows.h>
using std::string;

// �׽��ֵļ�����
class cgSocketListener
{
public:
	// ����������
	virtual void OnCreate(int nID, int nError){}
	virtual void OnClose(int nID, int nError){}

	// ���ӺͶ���
	virtual void OnConnect(int nID, int nError){}
	virtual void OnDisconnect(int nID, int nError){}

	// �շ�����
	virtual void OnSend(int nID, int nError){}
	virtual void OnReceive(int nID, int nError){}

	// ���ڷ��������յ�����
	virtual void OnAccept(int nID, int nError){}
};

// �ͻ����õ��׽���
class cgSocket
{
public:
	cgSocket(void);
	~cgSocket(void);

	// ����������
	virtual bool CreateSocket(unsigned uPort, LPCTSTR lpctAddr) = NULL;
	virtual void CloseSocket() = NULL;

	// ����:�ͻ�����
	virtual bool ConnectServer(LPCTSTR lpctAddr, unsigned uPort){return true;}

	// ���������ڷ�����
	virtual bool ListenConnection(int nNum = 5){return true;}
	virtual cgSocket* AcceptConnection(){return NULL;}

	// �շ�����
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
