#include "StdAfx.h"
#include "cgUIRichChar_Empty.h"
#include <cgMath.h>


cgUIRichChar_Empty::cgUIRichChar_Empty()
{
	m_nWidth = 0;
	m_nHeight = 0;
}

void cgUIRichChar_Empty::SetAttr( LPCTSTR attrName, LPCTSTR attrValue )
{
	 if (cgStrCmp(attrName , TEXT("width") ) == 0)
	 {
		m_nWidth = cgStrToULong(attrValue, NULL, 10);
	 }else if (cgStrCmp(attrName , TEXT("height") ) == 0)
	 {
		 m_nHeight = cgStrToULong(attrValue, NULL, 10);
	 }
}

cgSizeF cgUIRichChar_Empty::GetCharSize( cgID font )
{
	return cgSizeF(m_nWidth, m_nHeight);
}