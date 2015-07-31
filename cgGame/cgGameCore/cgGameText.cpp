#include "StdAfx.h"
#include "cgGameText.h"
#include "cgCamera.h"
#include "cgRender.h"


cgGameText::cgGameText(void)
{
	m_strName = "cgGameText";
	m_uBackColor = 0x00000000;
	m_idFont = 0;
	m_nTextStyle = DT_CENTER|DT_VCENTER;
}

cgGameText::cgGameText( const cgString& text, cgID font /*= 0*/, cgColor color, int style /*= DT_CENTER|DT_VCENTER*/ )
{
	m_strName = "cgGameText";

	m_uBackColor = 0x00000000;
	m_strText = text;
	m_idFont = font;
	m_nTextStyle = style;

	SetColor(color);
}

cgGameText::cgGameText( const string & strName ):cgGameObject(strName)
{
	m_uBackColor = 0x00000000;
	m_idFont = 0;
	m_nTextStyle = DT_CENTER|DT_VCENTER;
}

void cgGameText::SetText( cgString text )
{
	m_strText = text;
}

const cgString& cgGameText::GetText() const
{
	return m_strText;
}

void cgGameText::SetFont( cgID font )
{
	m_idFont = font;
}

cgID cgGameText::GetFont() const
{
	return m_idFont;
}

void cgGameText::SetTextStyle( int nStyle )
{
	m_nTextStyle = nStyle;
}

int cgGameText::GetTextStyle() const
{
	return m_nTextStyle;
}

void cgGameText::DoRenderSelf(cgCamera * renderCamera)
{
	cgVector center = GetWorldPosition();
	renderCamera->WorldToScreen(center);

	cgVector scale = GetWorldScale()*renderCamera->GetViewScale();

	cgRectF rect(center.x-m_kSize.w/2*scale.x, 
		center.y-m_kSize.h/2*scale.y,
		m_kSize.w*scale.x, 
		m_kSize.h*scale.y);

	cgRender::Get()->FillRect(rect, m_uBackColor);

	cgRender::Get()->RenderString(m_strText.c_str(), m_strText.length(),
		rect, m_idFont, 2, GetRenderColor(), m_nTextStyle, scale.x);
}

void cgGameText::SetBackColor( cgColor color )
{
	m_uBackColor = color;
}

cgColor cgGameText::GetBackColor()
{
	return m_uBackColor;
}
