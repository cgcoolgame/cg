#include "StdAfx.h"
#include "cgUIRender.h"

cgUIRender * cgUIRender::ms_pkRender = NULL;


cgUIRender::cgUIRender(void)
{
	ms_pkRender = this;
}


cgUIRender::~cgUIRender(void)
{
	ms_pkRender = NULL;
}


bool cgUIRender::Initialize( cgHwnd hWnd, int w, int h )
{
	m_hWnd = hWnd;
	m_nWidth = w;
	m_nHeight = h;

	return true;
}


cgUIRender * cgUIRender::GetRender()
{
	return ms_pkRender;
}
