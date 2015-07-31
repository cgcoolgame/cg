#include "StdAfx.h"
#include "cgUIRichChar_Font.h"


cgUIRichChar_Font::cgUIRichChar_Font(void)
{
	m_idFont = 0;
}

void cgUIRichChar_Font::SetAttr( LPCTSTR attrName, LPCTSTR attrValue )
{
	if (cgStrCmp(attrName , TEXT("id") ) == 0)
	{
		m_idFont = cgStrToULong(attrValue, NULL, 10) & 0xfeffffff;
	}
}

void cgUIRichChar_Font::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PushFont(m_idFont);
}

void cgUIRichChar_Font::Measure( cgUIRichPen & pen )
{
	pen.PushFont(m_idFont);
}

// -------------------------------------------------------------------

void cgUIRichChar_FontEnd::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PopFont();
}

void cgUIRichChar_FontEnd::Measure( cgUIRichPen & pen )
{
	pen.PopFont();
}
