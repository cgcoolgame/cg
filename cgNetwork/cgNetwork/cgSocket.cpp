#include "StdAfx.h"
#include "cgSocket.h"


cgSocket::cgSocket(void)
{
	m_pkListener = NULL;
	m_nID = 0;
}


cgSocket::~cgSocket(void)
{
}



void cgSocket::SetListener( cgSocketListener * pkListener )
{
	m_pkListener = pkListener;
}

void cgSocket::SetID( int nID )
{
	m_nID = nID;
}

int cgSocket::GetID()
{
	return m_nID;
}
