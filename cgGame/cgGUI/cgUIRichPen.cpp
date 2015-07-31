#include "StdAfx.h"
#include "cgUIRichPen.h"


cgUIRichPen::cgUIRichPen(void)
{
	m_uDefaultColor = 0xfeffffff;
	m_idDefaultFont = 0;
	m_bIfDefaultDrawUnderLine = false;
	m_bIfDefaultDrawDelLine = false;
}


cgUIRichPen::~cgUIRichPen(void)
{
}

void cgUIRichPen::SetDefaultColor( cgColor color )
{
	m_uDefaultColor = color;
}

cgColor cgUIRichPen::GetDefaultColor()
{
	return m_uDefaultColor;
}

void cgUIRichPen::PushColor( cgColor color )
{
	m_kColorStack.push(color);
}

void cgUIRichPen::PopColor()
{
	if (!m_kColorStack.empty())
		m_kColorStack.pop();
}

cgColor cgUIRichPen::GetCurColor()
{
	return m_kColorStack.empty()?m_uDefaultColor:m_kColorStack.top();
}
// ------------------------------------------------------------------

void cgUIRichPen::SetDefaultFont( cgID font )
{
	m_idDefaultFont = font;
}

cgID cgUIRichPen::GetDefaultFont()
{
	return m_idDefaultFont;
}

void cgUIRichPen::PushFont( cgID font )
{
	m_kFontStack.push(font);
}

void cgUIRichPen::PopFont()
{
	if (!m_kFontStack.empty())
		m_kFontStack.pop();
}

cgID cgUIRichPen::GetCurFont()
{
	return m_kFontStack.empty()?m_idDefaultFont:m_kFontStack.top();
}
// ------------------------------------------------------------------

void cgUIRichPen::SetDefaultDrawUnderLine( bool bDraw )
{
	m_bIfDefaultDrawUnderLine = bDraw;
}

bool cgUIRichPen::IfDefaultDrawUnderLine()
{
	return m_bIfDefaultDrawUnderLine;
}

void cgUIRichPen::PushUnderLine( bool bUnderLine /*= true*/ )
{
	m_kDrawUnderLineStack.push(bUnderLine);
}

void cgUIRichPen::PopUnderLine()
{
	if (!m_kDrawUnderLineStack.empty())
		m_kDrawUnderLineStack.pop();
}

bool cgUIRichPen::IfDrawUnderLine()
{
	return m_kDrawUnderLineStack.empty()?m_bIfDefaultDrawUnderLine:m_kDrawUnderLineStack.top();
}

// ------------------------------------------------------------------

void cgUIRichPen::SetDefaultDrawDelLine( bool bDraw )
{
	m_bIfDefaultDrawDelLine = bDraw;
}

bool cgUIRichPen::IfDefaultDrawDelLine()
{
	return m_bIfDefaultDrawDelLine;
}

void cgUIRichPen::PushDelLine( bool bDelLine /*= true*/ )
{
	m_kDrawDelLineStack.push(bDelLine);
}

void cgUIRichPen::PopDelLine()
{
	if (!m_kDrawDelLineStack.empty())
		m_kDrawDelLineStack.pop();
}

bool cgUIRichPen::IfDrawDelLine()
{
	return m_kDrawDelLineStack.empty()?m_bIfDefaultDrawDelLine:m_kDrawDelLineStack.top();
}


