#include "StdAfx.h"
#include "cgNetworkDef.h"
#include <afxsock.h>


cgNetworkDef::cgNetworkDef(void)
{
}


cgNetworkDef::~cgNetworkDef(void)
{
}

bool cgNetworkDef::NetworkInit()
{
	return AfxSocketInit();
}

void cgNetworkDef::NetworkDestroy()
{
	AfxSocketTerm();
}
