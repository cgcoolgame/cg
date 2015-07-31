#include "StdAfx.h"
#include "cgUICheck.h"
#include "cgUIRender.h"


cgUICheck::cgUICheck(void)
{
//	m_uBorderColor = 0xffafafaf;
//	m_uBackColor = 0xffefefef;
	m_strCursor = "IDC_HAND";
	m_uCheckedColor = 0xff4f4f4f;
	m_bIsChecked = false;
	m_strName = "cgUICheck";
}


cgUICheck::~cgUICheck(void)
{
}

bool cgUICheck::OnMessage( cgUIMsg msg, unsigned wparam, unsigned lparam )
{
	switch (msg)
	{
	case WM_LBUTTONUP:
		{	
			if (IsClickDown())
				SetCheck(!m_bIsChecked);

		}break;
	}
	return cgUIWidget::OnMessage(msg, wparam, lparam);
}

bool cgUICheck::IsChecked()
{
	return m_bIsChecked;
}

void cgUICheck::SetCheck( bool bChecked )
{
	if (m_bIsChecked != bChecked)
	{
		m_bIsChecked = bChecked;

		ReportDirty();
	}
}

void cgUICheck::SetCheckPic( LPCTSTR lpctNormal, LPCTSTR lpctChecked )
{
	m_spNormalPic = new cgUIImage(lpctNormal);
	m_spCheckedPic = new cgUIImage(lpctChecked);

	ReportDirty();
}

void cgUICheck::SetCheckPic( cgID idNormal, cgID idChecked )
{
	m_spNormalPic = new cgUIImage(idNormal);
	m_spCheckedPic = new cgUIImage(idChecked);

	ReportDirty();
}

void cgUICheck::SetCheckPic( cgUIImagePtr spNormal, cgUIImagePtr spChecked )
{
	m_spNormalPic = spNormal;
	m_spCheckedPic = spChecked;

	ReportDirty();
}

void cgUICheck::SetCheckColor( cgColor normalColor, cgColor checkedColor )
{
	m_uBackColor = normalColor;
	m_uCheckedColor = checkedColor;

	ReportDirty();
}


void cgUICheck::DrawBackPic(const cgRectF& clipRect)
{
	cgUIWidget::DrawBackPic(clipRect);

	DoDrawPic(m_bIsChecked?m_spCheckedPic:m_spNormalPic, m_kRect, clipRect);
}

void cgUICheck::DrawBackground( const cgRectF& clipRect )
{
	if (IfFillBackground())
	{
		cgColor uDrawColor = m_uBackColor;
		if (IsChecked())
			uDrawColor = m_uCheckedColor;
	
		cgUIRender::GetRender()->FillRect(clipRect, uDrawColor);
	}
}

