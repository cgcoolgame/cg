#include "StdAfx.h"
#include "cgButton.h"
#include "cgScaleBy.h"
#include "cgScaleTo.h"
#include "cgSrcImageManager.h"


cgButton::cgButton(void)
{
	m_strName = "cgButton";

	SetupParams();
}

cgButton::cgButton( const string & strName )
{
	m_strName = strName;

	SetupParams();
}

cgButton::cgButton( const string & strName, const cgVector& localPos, const cgSizeF& size )
{
	m_strName = strName;

	SetupParams();

	SetLocalPosition(localPos);
	SetSize(size);
}


cgButton::~cgButton(void)
{
}


void cgButton::SetupParams()
{
	m_strCursor = "hand";
}

// -------------------------------------------------------

void cgButton::DoProcessMouseEnter( int firstParam, int secondParam )
{
	if (m_spBackImage)
	{
		m_spBackImage->StopAllActions();
		m_spBackImage->StartAction(new cgScaleTo(1.05f, 1.05f, 0.05f));
	}
}

void cgButton::DoProcessMouseOut( int firstParam, int secondParam )
{
	if (m_spBackImage)
	{
		m_spBackImage->StopAllActions();
		m_spBackImage->StartAction(new cgScaleTo(1.0f, 1.0f, 0.05f));
	}
}

void cgButton::DoProcessMouseDown( int firstParam, int secondParam )
{
	if (m_spBackImage)
	{
		m_spBackImage->StopAllActions();
		m_spBackImage->StartAction(new cgScaleTo(0.95f, 0.95f, 0.05f));
	}
}

void cgButton::DoProcessMouseUp( int firstParam, int secondParam )
{
	if (m_spBackImage)
	{
		m_spBackImage->StopAllActions();
		m_spBackImage->StartAction(new cgScaleTo(1.05f, 1.05f, 0.05f));
	}
}


