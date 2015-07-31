#include "StdAfx.h"
#include "cgUIProgress.h"
#include "cgEngineTools.h"
#include "cgUIRender.h"


cgUIProgress::cgUIProgress(void)
{
	m_nRange = 100;
	m_nProgress = 0;
	m_fAimerPos = 0;
	m_fAimerSpeed = m_nRange;
	m_fProgressChangeTime = -1.0f;
	m_fAimerDelayTime = 0.0f;
	m_fLeftAimerDelayTime = 0.0f;
//	m_uBackColor = 0xffcfcfcf;
	m_uLayerColor = 0xffffff00;
	m_uCoverColor = 0xff0f8f0f;
}


cgUIProgress::~cgUIProgress(void)
{
}

void cgUIProgress::SetCoverImage( LPCTSTR cover )
{
	m_spCoverImage = new cgUIImage(cover);

	ReportDirty();
}

void cgUIProgress::SetCoverImage( cgID cover )
{
	m_spCoverImage = new cgUIImage(cover);

	ReportDirty();
}

void cgUIProgress::SetLayerImage( LPCTSTR layer )
{
	m_spLayerImage = new cgUIImage(layer);

	ReportDirty();
}

void cgUIProgress::SetLayerImage( cgID layer )
{
	m_spLayerImage = new cgUIImage(layer);

	ReportDirty();
}

void cgUIProgress::SetAimerImage( LPCTSTR aim )
{
	m_spAimerImage = new cgUIImage(aim);

	ReportDirty();
}

void cgUIProgress::SetAimerImage( cgID aim )
{
	m_spAimerImage = new cgUIImage(aim);

	ReportDirty();
}

void cgUIProgress::SetRange( int nRange )
{
	if (nRange > 0)
	{
		m_nRange = nRange;

		ReportDirty();
	}
}

int cgUIProgress::GetRange()const
{
	return m_nRange;
}

void cgUIProgress::SetProgress( int nProgress, bool bForceImmediate )
{
	if (nProgress < 0)
		nProgress = 0;
	if (nProgress > m_nRange)
		nProgress = m_nRange;

	if (nProgress != m_nProgress)
	{
		m_nProgress = nProgress;

		if (bForceImmediate || IsImmediate())
			m_fAimerPos = m_nProgress;
		else
		{
			// ����ʱ��Ϊ-1��������һ�θ���ʱ����Ϊ�仯ʱ�䡣
			m_fProgressChangeTime = -1.0f;
			m_fLeftAimerDelayTime = m_fAimerDelayTime;
		}

		ReportDirty();
	}
}

int cgUIProgress::GetProgress()const
{
	return m_nProgress;
}

int cgUIProgress::GetAimerPos()const
{
	return m_fAimerPos;
}


void cgUIProgress::SetAimerDelayTime( float fDelay )
{
	m_fAimerDelayTime = fDelay;
}

float cgUIProgress::GetAimerDelayTime()const
{
	return m_fAimerDelayTime;
}

void cgUIProgress::SetAimerSpeed( float fSpeed )
{
	m_fAimerSpeed = fSpeed;
	ReportDirty();
}

float cgUIProgress::GetAimerSpeed()const
{
	return m_fAimerSpeed;
}


bool cgUIProgress::IsImmediate() const
{
	return (m_nExtendStyle&cgProgressBarExtendStyle_Immediate) != 0;
}

void cgUIProgress::SetImmediate( bool bImmediate )
{
	if (IsImmediate() != bImmediate)
	{
		if (bImmediate)
			m_nExtendStyle |= cgProgressBarExtendStyle_Immediate;
		else
			m_nExtendStyle &= ~cgProgressBarExtendStyle_Immediate;

		ReportDirty();
	}
}

bool cgUIProgress::IsVertical() const
{
	return (m_nExtendStyle&cgProgressBarExtendStyle_Vertical) != 0;
}

void cgUIProgress::SetVertical( bool bVertical )
{
	if (IsVertical() != bVertical)
	{
		if (bVertical)
			m_nExtendStyle |= cgProgressBarExtendStyle_Vertical;
		else
			m_nExtendStyle &= ~cgProgressBarExtendStyle_Vertical;

		ReportDirty();
	}
}

void cgUIProgress::DrawBackPic( const cgRectF& clipRect )
{
	cgUIWidget::DrawBackPic(clipRect);

	DrawLayerImage(clipRect);
	DrawCoverImage(clipRect);
	DrawAimerImage(clipRect);
}

void cgUIProgress::DrawLayerImage( const cgRectF& clipRect )
{
	//if (!m_spLayerImage)
	//	return ;

	// ��׼��һֱ��׷�Ž����ܵģ�
	// ���Ը��ݺͽ��ȵĴ�С�ȽϾ�֪����׼���ķ����ˡ�
	// �Ӷ�֪����layer��cover��λ��
	// ��aimer���ڽ��ȵ�ʱ��cover�̶���layer����aimer���¼�
	// ��֮����aimerС�ڽ��ȵ�ʱ��layer�̶���cover����aimer������
	float fLayerPos = static_cast<float>(((int)m_fAimerPos) > m_nProgress?m_fAimerPos:m_nProgress);

	// layer����ռ�ľ���
	cgRectF layerRect(m_kRect.x, m_kRect.y, static_cast<int>(fLayerPos*m_kRect.w/m_nRange), m_kRect.h);
	
	// ���μ���
	cgRectF newClipRect;
	if (cgXGetIntersectRect(clipRect, layerRect, newClipRect))
	{
		// ���ѡ���˻��Ʊ�����ɫ������Ƶ�����ɫ
		if (IfFillBackground())
			cgUIRender::GetRender()->FillRect(newClipRect, m_uLayerColor);

		DoDrawPic(m_spLayerImage, m_kRect, newClipRect);
	}

}

void cgUIProgress::DrawCoverImage( const cgRectF& clipRect )
{
	//if (!m_spCoverImage)
	//	return ;

	float fCoverPos = static_cast<float>( ((int)m_fAimerPos) < m_nProgress?m_fAimerPos:m_nProgress) ;

	// cover����ռ�ı���
	cgRectF coverRect(m_kRect.x, m_kRect.y, static_cast<int>(fCoverPos*m_kRect.w/m_nRange), m_kRect.h);

	// ���μ���
	cgRectF newClipRect;
	if (cgXGetIntersectRect(clipRect, coverRect, newClipRect))
	{
		if (IfFillBackground())
			cgUIRender::GetRender()->FillRect(newClipRect, m_uCoverColor);

		DoDrawPic(m_spCoverImage, m_kRect, newClipRect);
	}
}

void cgUIProgress::DrawAimerImage( const cgRectF& clipRect )
{
	if (!m_spAimerImage)
		return ;

	cgRectF aimerRect;
	aimerRect.w = m_spAimerImage->GetWidth();
	aimerRect.h = m_spAimerImage->GetHeight();
	aimerRect.x = m_kRect.x+static_cast<int>(m_fAimerPos*m_kRect.w/m_nRange) - aimerRect.w/2;
	aimerRect.y = m_kRect.y+m_kRect.h/2 - aimerRect.h/2;

	// ���μ���
	cgRectF newClipRect;
	if (cgXGetIntersectRect(clipRect, aimerRect, newClipRect))
	{
		DoDrawPic(m_spAimerImage, aimerRect, newClipRect);
	}
}

// --------------------------------------------------------------------
void cgUIProgress::UpdateSelf( float fTime )
{
	UpdateAimerPos(fTime);
}

void cgUIProgress::UpdateAimerPos( float fTime )
{
	// ����ˣ��򲻹���
	if ( ((int)m_fAimerPos) == m_nProgress)
		return ;

	float fDelta = 0.0f;
	// ����ȣ���ʱ��С���㣬˵���ձ仯��
	if (m_fProgressChangeTime >= 0.0f)
		fDelta = fTime-m_fProgressChangeTime;

	m_fProgressChangeTime = fTime;

	if (m_fLeftAimerDelayTime > 0.0f)
	{
		m_fLeftAimerDelayTime -= fDelta;
		return ;
	}
	
	if (m_fAimerPos > m_nProgress)
	{
		m_fAimerPos -= fDelta*m_fAimerSpeed;
		if (m_fAimerPos < m_nProgress)
			m_fAimerPos = m_nProgress;
	}else
	{
		m_fAimerPos += fDelta*m_fAimerSpeed;
		if (m_fAimerPos > m_nProgress)
			m_fAimerPos = m_nProgress;
	}

	ReportDirty();

	
	//int nNewAimerPos = fDelta*nSpeed
}

void cgUIProgress::SetLayerColor( cgColor color )
{
	m_uLayerColor = color;
	ReportDirty();
}

cgColor cgUIProgress::GetLayerColor()
{
	return m_uLayerColor;
}

void cgUIProgress::SetCoverColor( cgColor color )
{
	m_uCoverColor = color;
	ReportDirty();
}

cgColor cgUIProgress::GetCoverColor()
{
	return m_uCoverColor;
}

