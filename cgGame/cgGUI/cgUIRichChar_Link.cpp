#include "StdAfx.h"
#include "cgUIRichChar_Link.h"
#include <shellapi.h>


cgUIRichChar_Link::cgUIRichChar_Link(void)
{
	m_uColor = 0xfe0000ff;
	m_uHotColor = 0xfeffff00;
	m_bIfUnderLine = true;
	m_bIfRClick = false;
	m_bIfHot = false;
	m_bIfUnderLineOnHot = true;
}


cgUIRichChar_Link::~cgUIRichChar_Link(void)
{
}

void cgUIRichChar_Link::SetAttr( LPCTSTR attrName, LPCTSTR attrValue )
{
	if (cgStrCmp(attrName , TEXT("func") ) == 0)
	{
		m_strFunc = attrValue;
	}else if (cgStrCmp(attrName , TEXT("param") ) == 0)
	{
		m_strParam = attrValue;
	}else if (cgStrCmp(attrName , TEXT("underline") ) == 0)
	{
		m_bIfUnderLine = cgStrCmp(attrValue, TEXT("true")) == 0;
	}else if (cgStrCmp(attrName , TEXT("rclick") ) == 0)
	{
		m_bIfRClick = cgStrCmp(attrValue, TEXT("true")) == 0;
	}else if (cgStrCmp(attrName , TEXT("color") ) == 0)
	{
		m_uColor = cgStrToULong(attrValue, NULL, 16) & 0xfeffffff;
	}else if (cgStrCmp(attrName , TEXT("hotcolor") ) == 0)
	{
		m_uHotColor = cgStrToULong(attrValue, NULL, 16) & 0xfeffffff;
	}
}

void cgUIRichChar_Link::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PushColor(m_bIfHot?m_uHotColor:m_uColor);
	pen.PushUnderLine(m_bIfHot?m_bIfUnderLineOnHot:m_bIfUnderLine);
}

void cgUIRichChar_Link::OnMouseIn()
{
	m_bIfHot = true;
}

void cgUIRichChar_Link::OnMouseOut()
{
	m_bIfHot = false;
}

void cgUIRichChar_Link::OnMouseMove()
{

}

void cgUIRichChar_Link::OnLButtonDown()
{
	if (!m_bIfRClick)
	{
		if (m_strFunc == TEXT("http"))
		{
			ShellExecute(NULL, NULL, m_strParam.c_str(), NULL, NULL, SW_SHOW);
		}else if (m_strFunc == TEXT("msg"))
		{
			MessageBox(NULL, m_strParam.c_str(), TEXT("Link"), MB_OK);
		}
	}
}

void cgUIRichChar_Link::OnRButtonDown()
{

}

// ------------------------------------------------------------------------

void cgUIRichChar_LinkEnd::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PopColor();
	pen.PopUnderLine();
}
