#include "StdAfx.h"
#include "cgWinSocket.h"


cgWinSocket::cgWinSocket(void)
{
}


cgWinSocket::~cgWinSocket(void)
{
	CloseSocket();
}

// -------------------------------------------------------------------
void cgWinSocket::OnReceive( int nErrorCode )
{
	if (m_pkListener)
		m_pkListener->OnReceive(m_nID, nErrorCode);
}

void cgWinSocket::OnSend( int nErrorCode )
{
	if (m_pkListener)
		m_pkListener->OnSend(m_nID, nErrorCode);
}

void cgWinSocket::OnConnect( int nErrorCode )
{
	if (m_pkListener)
		m_pkListener->OnConnect(m_nID, nErrorCode);
}

void cgWinSocket::OnClose( int nErrorCode )
{
	if (m_pkListener)
		m_pkListener->OnClose(m_nID, nErrorCode);
}


void cgWinSocket::OnAccept( int nErrorCode )
{
	if (m_pkListener)
		m_pkListener->OnAccept(m_nID, nErrorCode);
}


bool cgWinSocket::CreateSocket(unsigned uPort, LPCTSTR lpctAddr)
{
	BOOL bRet = Create(uPort, SOCK_STREAM, 63);

	if (m_pkListener)
		m_pkListener->OnCreate(m_nID, bRet);

	return bRet;
}

void cgWinSocket::CloseSocket()
{
	Close();
}

bool cgWinSocket::ConnectServer( LPCTSTR lpctAddr, unsigned uPort )
{
	return Connect(lpctAddr, uPort);
}

int cgWinSocket::SendData( void * pBuff, int nBuffLen )
{
	return Send(pBuff, nBuffLen);
}

int cgWinSocket::ReceiveData( void * pBuff, int nBuffLen )
{
	return Receive(pBuff, nBuffLen);
}

bool cgWinSocket::ListenConnection( int nNum /*= 5*/ )
{
	return Listen(nNum);
}

cgSocket* cgWinSocket::AcceptConnection(  )
{
	cgWinSocket * pkNewSocket = new cgWinSocket;
	if (!Accept(*pkNewSocket))
	{
		delete pkNewSocket;
		return NULL;
	}
	return pkNewSocket;
}
