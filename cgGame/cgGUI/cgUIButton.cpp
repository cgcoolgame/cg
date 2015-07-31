#include "StdAfx.h"
#include "cgUIButton.h"
#include "cgUIRender.h"


cgUIButton::cgUIButton(void)
{
	SetupParams();
	m_strName = "cgUIButton";
}

cgUIButton::cgUIButton( const string & strName )
{
	SetupParams();
	m_strName = strName;
}


cgUIButton::~cgUIButton(void)
{
}


void cgUIButton::SetupParams()
{
	m_strCursor = "IDC_HAND";
	m_uHotColor = 0xffdfdfdf;
	m_uPressColor = 0xffbfbfbf;
	m_uDisableColor = 0xff0f0f0f;
}

// -------------------------------------------------------------------------------

void cgUIButton::SetButtonPic( LPCTSTR lpctNormal, LPCTSTR lpctHot, 
	LPCTSTR lpctPress, LPCTSTR lpctDisable )
{
	m_spNormalPic = new cgUIImage(lpctNormal);
	m_spHotPic = new cgUIImage(lpctHot);
	m_spPressPic = new cgUIImage(lpctPress);
	m_spDisablePic = new cgUIImage(lpctDisable);

	ReportDirty();
}

void cgUIButton::SetButtonPic( cgID idNormal, cgID idHot,
	cgID idPress, cgID idDisable )
{
	m_spNormalPic = new cgUIImage(idNormal);
	m_spHotPic = new cgUIImage(idHot);
	m_spPressPic = new cgUIImage(idPress);
	m_spDisablePic = new cgUIImage(idDisable);

	ReportDirty();
}

void cgUIButton::SetButtonPic( cgUIImagePtr spNormal, cgUIImagePtr spHot, 
	cgUIImagePtr spPress, cgUIImagePtr spDisable )
{
	m_spNormalPic = spNormal;
	m_spHotPic = spHot;
	m_spPressPic = spPress;
	m_spDisablePic = spDisable;

	ReportDirty();
}

void cgUIButton::SetButtonColor( cgColor uNormalColor, 
	cgColor uHotColor, 
	cgColor uPressColor, 
	cgColor uDisableColor )
{
	m_uBackColor = uNormalColor;
	m_uHotColor = uHotColor;
	m_uPressColor = uPressColor;
	m_uDisableColor = uDisableColor;

	ReportDirty();
}


void cgUIButton::DrawBackPic(const cgRectF& clipRect)
{
	cgUIWidget::DrawBackPic(clipRect);

	cgUIImagePtr ptr;
	if (!IsEnable())
		ptr = m_spDisablePic;
	else if (IsClickDown())
		ptr = m_spPressPic;
	else if (IsMouseOver())
		ptr = m_spHotPic;
	else
		ptr = m_spNormalPic;
	
	DoDrawPic(ptr, m_kRect, clipRect);
}


void cgUIButton::DrawBackground( const cgRectF& clipRect )
{
	if (IfFillBackground())
	{
		cgColor uDrawColor = m_uBackColor;
		if (!IsEnable())
			uDrawColor = m_uDisableColor;
		else if (IsClickDown())
			uDrawColor = m_uPressColor;
		else if (IsMouseOver())
			uDrawColor = m_uHotColor;

		cgUIRender::GetRender()->FillRect(clipRect, uDrawColor);
	}
}
