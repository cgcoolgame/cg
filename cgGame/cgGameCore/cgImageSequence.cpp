#include "StdAfx.h"
#include "cgImageSequence.h"



/************************************************************************/
/*                                                                      */
/************************************************************************/

cgImageFrame::cgImageFrame()
{
	m_spImage = NULL;
	m_fDuration = 0.0f;
	m_fOffX = 0.0f;
	m_fOffY = 0.0f;
}

cgImageFrame::cgImageFrame( cgImagePtr spImage, float fDuration )
{
	m_spImage = spImage;
	m_fDuration = fDuration;
	m_fOffX = 0.0f;
	m_fOffY = 0.0f;
}

float cgImageFrame::GetDuration()
{
	return m_fDuration;
}

cgImagePtr cgImageFrame::GetImage()
{
	return m_spImage;
}

void cgImageFrame::SetImage( cgImagePtr spImage )
{
	m_spImage = spImage;
}

void cgImageFrame::SetDuration( float fDuration )
{
	m_fDuration = fDuration;
}

void cgImageFrame::SetFrameOffset( float xOff, float yOff )
{
	m_fOffX = xOff;
	m_fOffY = yOff;
}

float cgImageFrame::GetFrameOffsetX()
{
	return m_fOffX;
}

float cgImageFrame::GetFrameOffsetY()
{
	return m_fOffY;
}

// ------------------------------------------------------------------------------
cgImageSequence::cgImageSequence()
{
	m_uCurFrameIndex = 0;
	m_fSequenceTime = 0.0f;
	m_spCurImage = new cgGameSprite;
	AttachChild(&m_spCurImage);	// 添加一个子节点
}

void cgImageSequence::DoUpdateSelf( float fDeltaTime )
{
	if (m_kFrameList.empty())
		return ;

	cgImageFramePtr spCurFrame = GetFrameByIndex(m_uCurFrameIndex);
	if (!spCurFrame)
		return;

	m_fSequenceTime += fDeltaTime;
	if (m_fSequenceTime >= spCurFrame->GetDuration())
	{
		m_fSequenceTime -= spCurFrame->GetDuration();
		SetCurFrameIndex(m_uCurFrameIndex+1);
	}
}

void cgImageSequence::AddFrame( cgImageFramePtr spFrame )
{
	if (spFrame)
	{
		m_kFrameList.push_back(spFrame);
	}
}

void cgImageSequence::Reset()
{
	SetCurFrameIndex(0);
}

unsigned cgImageSequence::GetCurFrameIndex()
{
	return m_uCurFrameIndex;
}

void cgImageSequence::SetCurFrameIndex( unsigned uIndex )
{
	if (m_kFrameList.empty())
		return ;

	m_uCurFrameIndex = uIndex;

	// 循环播放
	if (m_uCurFrameIndex >= m_kFrameList.size())
		m_uCurFrameIndex = 0;

	cgImageFramePtr spFrame = GetFrameByIndex(m_uCurFrameIndex);
	m_spCurImage->SetImage( spFrame->GetImage());
	m_spCurImage->SetSize(spFrame->GetImage()->GetWidth(), spFrame->GetImage()->GetHeight());
	m_spCurImage->SetLocalPosition(spFrame->GetFrameOffsetX(), spFrame->GetFrameOffsetY());

	SetSize(m_spCurImage->GetSize());
}

cgImageFramePtr cgImageSequence::GetFrameByIndex( unsigned uIndex )
{
	if (uIndex < m_kFrameList.size())
		return m_kFrameList[uIndex];

	return NULL;
}
