#include "StdAfx.h"
#include "cgUIRichChar_Image.h"
#include "cgUIRender.h"


cgUIRichChar_Image::cgUIRichChar_Image(void)
{
}

void cgUIRichChar_Image::SetAttr( LPCTSTR attrName, LPCTSTR attrValue )
{
	if (cgStrCmp(attrName , TEXT("path") ) == 0)
	{
		m_spImage = new cgUIImage(attrValue);
	}else if (cgStrCmp(attrName , TEXT("id") ) == 0)
	{
		m_spImage = new cgUIImage(cgStrToULong(attrValue, NULL, 10));
	}
}

cgSizeF cgUIRichChar_Image::GetCharSize( cgID font )
{
	return m_spImage?cgSizeF(m_spImage->GetWidth(), m_spImage->GetHeight()):cgSizeF();
}

void cgUIRichChar_Image::Draw( cgUIRichPen & pen, int x, int y )
{
	m_spImage->DrawToPoint(x, y);
}
