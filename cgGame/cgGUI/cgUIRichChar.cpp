#include "StdAfx.h"
#include "cgUIRichChar.h"
#include "cgUIRichChar_Color.h"
#include "cgUIRichChar_Font.h"
#include "cgUIRichChar_UnderLine.h"
#include "cgUIRichChar_DelLine.h"
#include "cgUIRichChar_Link.h"
#include "cgUIRichChar_EndLine.h"
#include "cgUIRichChar_Empty.h"
#include "cgUIRichChar_Image.h"


cgUIRichChar::cgUIRichChar(void)
{
}


cgUIRichChar::~cgUIRichChar(void)
{
}


void cgUIRichChar::SetTypeString( const cgString & strType )
{
	m_strType = strType;
}


const cgString & cgUIRichChar::GetTypeString()
{
	return m_strType;
}

void cgUIRichChar::SetAttr( LPCTSTR attrName, LPCTSTR attrValue )
{

}

void cgUIRichChar::Draw(cgUIRichPen & pen, int x, int y)
{

}

LPCTSTR cgUIRichChar::GetRawString()
{
	return m_strRawString.c_str();
}

void cgUIRichChar::SetRawString( LPCTSTR rawStr )
{
	m_strRawString = rawStr;
}

cgSizeF cgUIRichChar::GetCharSize(cgID font)
{
	return cgSizeF();
}

bool cgUIRichChar::NeedChangeLine()
{
	return false;
}

void cgUIRichChar::Measure( cgUIRichPen & pen )
{

}

void cgUIRichChar::OnMouseIn()
{

}

void cgUIRichChar::OnMouseOut()
{

}

void cgUIRichChar::OnMouseMove()
{

}

void cgUIRichChar::OnLButtonDown()
{

}

void cgUIRichChar::OnRButtonDown()
{

}
