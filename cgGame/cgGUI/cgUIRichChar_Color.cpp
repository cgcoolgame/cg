#include "StdAfx.h"
#include "cgDefine.h"
#include "cgUIRichChar_Color.h"


cgUIRichChar_Color::cgUIRichChar_Color(void)
{
	m_uColor = 0xfeffffff;
}

void cgUIRichChar_Color::SetAttr( LPCTSTR attrName, LPCTSTR attrValue )
{
	if (cgStrCmp(attrName , TEXT("value") ) == 0)
	{
		m_uColor = cgStrToULong(attrValue, NULL, 16) & 0xfeffffff;
	}
}

void cgUIRichChar_Color::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PushColor(m_uColor);
}

// ------------------------------------------------------------------------
void cgUIRichChar_ColorEnd::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PopColor();
}
