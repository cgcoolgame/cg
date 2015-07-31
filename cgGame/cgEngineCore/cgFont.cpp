#include "StdAfx.h"
#include "cgFont.h"
#include "cgRenderImpl.h"
#include "cgRender.h"
#include "cgWinApp.h"


cgFont::cgFont()
{
	m_id = CG_INVALID_ID;
	m_fBkTexXOff = 0.0f;
	m_fBkTexYOff = 0.0f;
	m_pkRenderImpl = NULL;
	m_nBkTexWidth = CG_DEFAULT_FONT_TEXTURE_WITH;
	m_nBkTexHeight = CG_DEFAULT_FONT_TEXTURE_HEIGHT;
}


cgFont::~cgFont(void)
{
}

bool cgFont::Initialize( cgRenderImpl * pkRenderImpl, const cgFontConfig & kConfig )
{
	m_pkRenderImpl = pkRenderImpl;

	m_kConfig = kConfig;

	m_id = m_pkRenderImpl->AddFont(kConfig);
	if (m_id == CG_INVALID_ID)
		return false;

	if (m_kConfig.szPicPath[0])
		m_spExtendTexImg = cgImage::LoadFromFile(m_kConfig.szPicPath);

	LoadExtendTextureAndWords();

	return true;
}

// -------------------------------------------------------------------------------------

bool cgFont::LoadExtendTextureAndWords()
{
	if (m_spExtendTexImg)
	{
		float fXOff = 0;
		float fYOff = 0;
		for (unsigned i = 0; m_kConfig.szText[i]; ++i)
		{
			if ( fXOff+m_kConfig.uWidth > m_spExtendTexImg->GetWidth() )
			{
				fXOff = 0.0f;
				fYOff += m_kConfig.uHeight;
			}

			cgRectF rect(fXOff, fYOff, m_kConfig.uWidth, m_kConfig.uHeight);

			m_spWordImageList[ m_kConfig.szText[i] ] =
				cgImage::ClipFromImage(&m_spExtendTexImg, rect);

			fXOff += m_kConfig.uWidth;
		}
	}
	
	return true;
}


// -------------------------------------------------------------------------------------------------------

cgImagePtr cgFont::RenderCharToTexture( TCHAR ch )
{
	if (!m_spBuffTexImg)
	{
		// 如果后台贴图没创建，则创建之
		m_spBuffTexImg = cgImage::CreateImage(m_nBkTexWidth, m_nBkTexHeight);
	}

	// 由renderImpl来计算字符的宽度
	int nCharWidth = m_pkRenderImpl->CalcTextWidth(&ch, 1, m_id);

	//if (nCharWidth == 0)
	//	nCharWidth = m_kConfig.uWidth/2;

	// 如果新加的字符超出了后台贴图的宽度，则换行
	if (m_fBkTexXOff+nCharWidth > m_nBkTexWidth)
	{
		m_fBkTexXOff = 0.0f;
		m_fBkTexYOff += m_kConfig.uHeight+1;
	}

	cgRectF rect(m_fBkTexXOff, m_fBkTexYOff, nCharWidth, m_kConfig.uHeight);

	// 把后台贴图当作渲染目标
	m_pkRenderImpl->PushRenderTarget(m_spBuffTexImg->GetTextureID());
	m_pkRenderImpl->ClearRect(rect);
	m_pkRenderImpl->SetRenderDirty();
//	m_pkRenderImpl->EnableTextureFilter(true);
	m_pkRenderImpl->RenderTextDirectly(&ch, 1, rect, m_id, 0xffffffff, DT_LEFT|DT_TOP);
//	m_pkRenderImpl->EnableTextureFilter(true);
	m_pkRenderImpl->PopRenderTarget();

	m_fBkTexXOff += nCharWidth+1;

	// 已经绘制到了后台贴图，把这个字符所占的区域当作一个独立图片存起来
	cgImagePtr spWordImage = cgImage::ClipFromImage(&m_spBuffTexImg, rect);
	m_spWordImageList[ch] =  spWordImage;

	return spWordImage;
}


// -----------------------------------------------------------------------------------
#ifdef _DEBUG
#include "cgEngineTools.h"
void cgFont::ShowSelf()
{
	if (cgXIsKeyPressed(VK_CONTROL))
	{
		if (m_spBuffTexImg)
			m_spBuffTexImg->DrawToPoint(0, 100);
		if (m_spExtendTexImg)
			m_spExtendTexImg->DrawToPoint(0, 200);
	}

}

#endif

const cgFontConfig * cgFont::GetConfig()
{
	return &m_kConfig;
}

cgImagePtr cgFont::GetCharImage( TCHAR ch )
{
	cgImagePtr & sp = m_spWordImageList[ch];
	if (!sp)
		sp = RenderCharToTexture(ch);

	return sp;
}

// ----------------------------------------------------------------------------------------------------
float cgFont::GetCharWidthInPixel( TCHAR ch )
{
	cgImagePtr spImage = GetCharImage(ch);
	if (spImage)
		return spImage->GetWidth();

	return 0;
}


cgSizeF cgFont::GetCharSizeInPixel( TCHAR ch )
{
	cgImagePtr spImage = GetCharImage(ch);
	if (spImage)
		return cgSizeF(spImage->GetWidth(), spImage->GetHeight()) ;

	return cgSizeF();
}

void cgFont::DrawChar( TCHAR ch, float x, float y, cgColor color, float scale)
{
	cgImagePtr spImage = GetCharImage(ch);
	if (spImage)
		spImage->DrawToRect(x, y, spImage->GetWidth()*scale, spImage->GetHeight()*scale, color);
}

void cgFont::Reset()
{
	for (unsigned i = 0; i < CG_MAX_WORD_PER_FONT; ++i)
	{
		m_spWordImageList[i] = NULL;
	}

	m_fBkTexXOff = 0.0f;
	m_fBkTexYOff = 0.0f;

	LoadExtendTextureAndWords();
}
