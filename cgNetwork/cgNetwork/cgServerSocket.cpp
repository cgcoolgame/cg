#include "StdAfx.h"
#include "cgServerSocket.h"


cgServerSocket::cgServerSocket(void)
{
}


cgServerSocket::~cgServerSocket(void)
{
}

bool cgServerSocket::Initialize( LPCTSTR lpctSvrAddr, UINT uBindPort )
{
	if (!Create(uBindPort))
		return false;

	Listen();
	return true;
}

// ------------------------------------------------------------------------

void cgServerSocket::OnAccept( int nErrorCode )
{
	Accept(m_kConnectSocket);

	//char szBuff[] = "Welcome !";
	//m_kConnectSocket.Send(szBuff, sizeof(szBuff));
}
