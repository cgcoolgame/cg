#include "StdAfx.h"
#include "cgRender.h"
#include "cgRenderImpl.h"
#include "cgFontManager.h"
#include "cgFont.h"
#include "cgPlatform.h"

/************************************************************************/
// 夜深了，明天周末还要加班，很困，但是不愿睡，坚持做完吧[3/8/2014 master]      
/************************************************************************/
#define _USE_HARDWARE_FONT_

cgRender::cgRender()
{
	m_pkRenderImpl = NULL;
}

cgRender::~cgRender()
{
	cgFontManager::Destroy();
	delete m_pkRenderImpl;
}

// --------------------------------------------------------------------------------------
bool cgRender::Initialize( cgHwnd hWnd, int nWidth, int nHeight )
{
	m_pkRenderImpl = cgPlatform::Instance()->CreateRenderImpl();

	if (!m_pkRenderImpl->Initialize(hWnd, nWidth, nHeight))
		return false;

	if (!cgFontManager::Create()->Initialize(m_pkRenderImpl))
		return false;

	return true;
}


bool cgRender::Resize( int nWidth, int nHeight )
{
	cgFontManager::Get()->PreOnLostDevice();
	return m_pkRenderImpl->Resize(nWidth, nHeight);
}


// ---------------------------------------------------------------------------------------

bool cgRender::SetViewPort( const cgRectF& rect )
{
	return m_pkRenderImpl->SetViewPort(rect);
}

void cgRender::GetViewPort( cgRectF& rect )
{
	m_pkRenderImpl->GetViewPort(rect);
}

void cgRender::ClearBack( cgColor color )
{
	m_pkRenderImpl->ClearBack(color);
}


void cgRender::ClearRect( const cgRectF& clearRect )
{
	m_pkRenderImpl->ClearRect(clearRect);
}

void cgRender::BeginRender()
{
	m_pkRenderImpl->BeginRender();
}

void cgRender::EndRender()
{
#ifdef _DEBUG
	cgFontManager::Get()->FindFont(2)->ShowSelf();
#endif

	m_pkRenderImpl->EndRender();
}

void cgRender::Present()
{
	m_pkRenderImpl->Present();
}

cgID cgRender::LoadTexture( LPCTSTR lpctImagePath, int nOption /*= NULL*/ )
{
	return m_pkRenderImpl->LoadTexture(lpctImagePath , nOption);
}

cgID cgRender::CreateTexture( int nWidth, int nHeight )
{
	return m_pkRenderImpl->CreateTexture(nWidth, nHeight);
}

bool cgRender::ReleaseTexture( cgID id )
{
	return m_pkRenderImpl->ReleaseTexture(id);
}

void cgRender::RenderTexture( cgID id, const cgRectF& srcRect, const cgRectF& destRect, cgColor color )
{
	m_pkRenderImpl->RenderTexture(id, srcRect, destRect, color);
}


void cgRender::RenderPolygon( const cgRenderVertex* pkVertexList, unsigned uVertexNum, 
	cgID idTexImage  )
{
	m_pkRenderImpl->RenderPolygon(pkVertexList, uVertexNum, idTexImage);
}


cgSize cgRender::GetTextureSize( cgID id )
{
	return m_pkRenderImpl->GetTextureSize(id);
}

void cgRender::FillRect( const cgRectF& destRect, cgColor color )
{
	m_pkRenderImpl->FillRect(destRect, color);
}

void cgRender::DrawBox( const cgRectF& destRect, cgColor color )
{
	m_pkRenderImpl->DrawBox(destRect, color);
}

void cgRender::RenderLine( const cgPoint& fromPoint, const cgPoint& toPoint, cgColor color )
{
	m_pkRenderImpl->DrawLine(fromPoint, toPoint, color);
}

void cgRender::RenderPoint( const cgPoint& point, cgColor color )
{
	m_pkRenderImpl->DrawPoint(point, color);
}

void cgRender::RenderString( LPCTSTR lpctText, int nTextLen,
	float x, float y, cgID font, cgColor color )
{
#ifdef _USE_HARDWARE_FONT_
	cgFont * pkFont = cgFontManager::Get()->FindFont(font);
	if (!pkFont)
		return ;

	for (int i = 0; i < nTextLen; ++i)
	{
		pkFont->DrawChar(lpctText[i], x, y, color);
		x += pkFont->GetCharWidthInPixel(lpctText[i]);
	}
#else
	m_pkRenderImpl->RenderTextDirectly(lpctText, nTextLen, cgRectF(x, y, 1000, 1000), font, color, DT_LEFT);

#endif

}

void cgRender::RenderString( LPCTSTR lpctText, int nTextLen, 
	const cgRectF& rect, cgID font, float space ,
	cgColor color, unsigned style, float scale )
{
	
#ifdef _USE_HARDWARE_FONT_

	cgFont * pkFont = cgFontManager::Get()->FindFont(font);
	if (!pkFont)
		return ;

	// 计算字符串占得宽高
	float textWidth = rect.w;
	float textHeight = rect.h;
	MeasureString(lpctText, nTextLen, font, textWidth, textHeight, space, scale);
	
	// 计算字符串绘制的起始位置
	float beginX = rect.x;
	float beginY = rect.y;

	if (style&DT_RIGHT)
		beginX = rect.x+rect.w-textWidth;
	
	if (style&DT_CENTER)
		beginX = (rect.w-textWidth)/2+rect.x;
	
	if (style&DT_BOTTOM)
		beginY = rect.y+rect.h-textHeight;
	
	if (style&DT_VCENTER)
		beginY = (rect.h-textHeight)/2+rect.y;
	
	float nFontHeight = pkFont->GetConfig()->uHeight*scale;

	float drawX = beginX;
	float drawY = beginY;

	for (int i = 0; i < nTextLen; ++i)
	{
		TCHAR ch = lpctText[i];
		
		if (ch == TEXT('\n') )
		{
			drawY += (space+nFontHeight);
			drawX = beginX;
		}else
		{
			float charWidth = pkFont->GetCharWidthInPixel(ch)*scale;
			if(drawX + charWidth > beginX+textWidth+0.5f)
			{
				drawY += (space+nFontHeight);
				drawX = beginX;
			}

			pkFont->DrawChar(ch, drawX, drawY, color, scale);
			drawX += charWidth;
		}
	
		
	}

#else
	m_pkRenderImpl->RenderTextDirectly(lpctText, nTextLen, rect, font, color, style);
	m_pkRenderImpl->SetRenderDirty();
#endif
}

bool cgRender::PushRenderTarget( cgID id )
{
	return m_pkRenderImpl->PushRenderTarget(id);
}

bool cgRender::PopRenderTarget()
{
	return m_pkRenderImpl->PopRenderTarget();
}

void cgRender::SetRenderDirty()
{
	m_pkRenderImpl->SetRenderDirty();
}

void cgRender::ScreenShot( LPCTSTR lpctSavePath, cgScreenShotImageFormat enmFormat )
{
	m_pkRenderImpl->ScreenShot(lpctSavePath, enmFormat);
}

cgRenderSurface * cgRender::CreateRenderSurface( int w, int h, int nOpertion /*= 0*/ )
{
	return m_pkRenderImpl->CreateRenderSurface(w, h, nOpertion);
}

bool cgRender::PresentRenderSurface( cgRenderSurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect )
{
	return m_pkRenderImpl->PresentRenderSurface(pkSurface, srcRect, destRect);
}

int cgRender::GetRenderCharWidth( TCHAR ch, cgID idFont )
{
	int nW = 0;
	cgFont * pkFont = cgFontManager::Get()->FindFont(idFont);
	if (pkFont)
	{
		nW = pkFont->GetCharWidthInPixel(ch);
	}

	return nW;
}

void cgRender::SetAmbientLight( cgColor light )
{
	m_pkRenderImpl->SetAmbientLight(light);
}

cgColor cgRender::GetAmbientLight()
{
	return m_pkRenderImpl->GetAmbientLight();
}

cgSizeF cgRender::GetRenderCharSize( TCHAR ch, cgID idFont )
{
	cgFont * pkFont = cgFontManager::Get()->FindFont(idFont);
	if (pkFont)
		return pkFont->GetCharSizeInPixel(ch);
	
	return cgSizeF(0, 0);
}

bool cgRender::MeasureString( LPCTSTR text, int len, cgID font,
	float & w, float & h, 
	float space, float scale )
{
	cgFont * pkFont = cgFontManager::Get()->FindFont(font);
	if (!pkFont || len <= 0)
		return false;

	float fontHeight = pkFont->GetConfig()->uHeight*scale;

	float textWidth = 0.0f;
	float textHeight = fontHeight;

	float charX = 0.0f;
	
	for (int i = 0; i < len; ++i)
	{
		if (text[i] == TEXT('\n'))
		{
			textHeight +=(space+fontHeight);
			textWidth = max(textWidth, charX);
			charX = 0;
		}else
		{
			float charWith = pkFont->GetCharWidthInPixel(text[i])*scale;
			if (charX+charWith > w)
			{
				textHeight +=(space+fontHeight);
				textWidth = max(textWidth, charX);
				charX = 0;
			}

			charX += charWith;
		}
	}
	w = max(textWidth, charX);
	h = textHeight;

	return true;
}
