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
			// 设置时间为-1，表明下一次更新时计算为变化时间。
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

	// 瞄准器一直是追着进度跑的，
	// 所以根据和进度的大小比较就知道瞄准器的方向了。
	// 从而知道了layer和cover的位置
	// 当aimer大于进度的时候，cover固定，layer跟着aimer往下减
	// 反之，当aimer小于进度的时候，layer固定，cover跟着aimer往上涨
	float fLayerPos = static_cast<float>(((int)m_fAimerPos) > m_nProgress?m_fAimerPos:m_nProgress);

	// layer的所占的矩形
	cgRectF layerRect(m_kRect.x, m_kRect.y, static_cast<int>(fLayerPos*m_kRect.w/m_nRange), m_kRect.h);
	
	// 二次剪切
	cgRectF newClipRect;
	if (cgXGetIntersectRect(clipRect, layerRect, newClipRect))
	{
		// 如果选择了绘制背景颜色，则绘制底条颜色
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

	// cover的所占的比例
	cgRectF coverRect(m_kRect.x, m_kRect.y, static_cast<int>(fCoverPos*m_kRect.w/m_nRange), m_kRect.h);

	// 二次剪切
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

	// 二次剪切
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
	// 相等了，则不管了
	if ( ((int)m_fAimerPos) == m_nProgress)
		return ;

	float fDelta = 0.0f;
	// 不相等，且时间小于零，说明刚变化过
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

