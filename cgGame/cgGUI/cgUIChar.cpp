#include "StdAfx.h"
#include "cgUIChar.h"
#include "cgUIRender.h"


cgUIChar::cgUIChar(void)
{
}


cgUIChar::~cgUIChar(void)
{
}

void cgUIChar::Draw(cgUIRichPen & pen, int x, int y)
{
	cgUIRender::GetRender()->DrawUIText(m_strRawString.c_str(), 1, x, y, 
		pen.GetCurFont(), pen.GetCurColor());

	cgSizeF charSize = GetCharSize(pen.GetCurFont());
	if (pen.IfDrawUnderLine())
	{
		cgUIRender::GetRender()->DrawLine(cgPoint(x, y+charSize.h),
			cgPoint(x+charSize.w, y+charSize.h), pen.GetCurColor());
	}
	
	if (pen.IfDrawDelLine())
	{
		cgUIRender::GetRender()->DrawLine(cgPoint(x, y+charSize.h/2),
			cgPoint(x+charSize.w, y+charSize.h/2), pen.GetCurColor());
	}
}

cgSizeF cgUIChar::GetCharSize(cgID font)
{
	return cgUIRender::GetRender()->GetUICharSize(m_strRawString[0], font);
}
