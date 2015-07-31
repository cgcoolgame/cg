#include "StdAfx.h"
#include "cgGdiplusRender.h"
#include <atlbase.h>
#include <atlwin.h>
#include <exdisp.h>
#include <cgEngineTools.h>

// ---------------------------------------------------------------------
#pragma comment(lib,"atl")  
#pragma comment(lib,"User32.lib")  

static CComModule _Module;


cgGdiplusRender::cgGdiplusRender(void):
m_kImageStorage(64)
{
}


cgGdiplusRender::~cgGdiplusRender(void)
{
	GdiplusFontPtrList::iterator it = m_kFontList.begin();
	for (; it != m_kFontList.end(); ++it)
		delete *it;

	if (m_pkGraphics)
		m_pkGraphics->ReleaseHDC((HDC)m_pkBkSurface->GetContent());

	delete m_pkBkSurface;

	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

bool cgGdiplusRender::Initialize( cgHwnd hWnd, int w, int h )
{
	if (!cgUIRender::Initialize(hWnd, w, h))
		return false;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	m_kBlend.BlendOp=AC_SRC_OVER; //theonlyBlendOpdefinedinWindows2000
	m_kBlend.BlendFlags=0; //nothingelseisspecial...
	m_kBlend.AlphaFormat=AC_SRC_ALPHA; //...
	m_kBlend.SourceConstantAlpha=255;//AC_SRC_ALPHA 

	m_pkBkSurface = CreateUISurface(w, h);

	if (!m_pkBkSurface)
		return false;

	m_pkGraphics = new Gdiplus::Graphics((HDC)m_pkBkSurface->GetContent());

	if (!LoadFonts())
		return false;

	return true;
}


void cgGdiplusRender::SetAlpha( BYTE alpha )
{
	m_kBlend.SourceConstantAlpha = alpha;
}


bool cgGdiplusRender::PushClipRect( const cgRectF& clipRect )
{
	Gdiplus::Rect kOregionRect;
	m_pkGraphics->GetClipBounds(&kOregionRect);

	cgRectF oldRect(kOregionRect.X, kOregionRect.Y, kOregionRect.Width, kOregionRect.Height);
	cgRectF finalRect;
	if (cgXGetIntersectRect(oldRect, clipRect, finalRect))
	{
		Gdiplus::Rect kNewRect(finalRect.x, finalRect.y, finalRect.w, finalRect.h);
		m_pkGraphics->SetClip(kNewRect);

		m_kClipRectStack.push(kOregionRect);

		return true;
	}

	return false;
}

void cgGdiplusRender::PopClipRect()
{
	Gdiplus::Rect clipRect = m_kClipRectStack.top();
	m_kClipRectStack.pop();
	m_pkGraphics->SetClip(clipRect);
}

void cgGdiplusRender::ClearRect( const cgRectF& rect )
{
	m_pkGraphics->Clear(Gdiplus::Color(0, 0, 0, 0));
}

void cgGdiplusRender::BeginRender()
{
//	m_pkGraphics->Clear(Gdiplus::Color(0, 0, 0, 0));
}

void cgGdiplusRender::EndRender()
{
}

void cgGdiplusRender::Display()
{
	SIZE size={m_nWidth, m_nHeight};
	POINT pt={0, 0};

	//更新窗口
	if (!UpdateLayeredWindow( m_hWnd, NULL, NULL,
		&size, (HDC)m_pkBkSurface->GetContent(), &pt, 0, &m_kBlend, 2))
	{
		DWORD dwError = ::GetLastError();
		dwError = dwError;
	}
}

bool cgGdiplusRender::OnSizeChanged( int w, int h )
{
	return true;
}

cgID cgGdiplusRender::LoadImage( LPCTSTR path )
{
	return m_kImageStorage.Add( LoadImageFromFile(path));
}

cgID cgGdiplusRender::LoadImage( cgID resID )
{
	return m_kImageStorage.Add(LoadImageFromResource(resID, TEXT("PNG")));
}	


bool cgGdiplusRender::ReleaseImage( cgID image )
{
	Gdiplus::Image * pkImage = m_kImageStorage.Remove(image);
	if (pkImage)
		delete pkImage;

	return pkImage != NULL;
}

cgSize cgGdiplusRender::GetImageSize( cgID image )
{
	cgSize size;
	Gdiplus::Image* pkImage = m_kImageStorage.Find(image);
	if (pkImage)
	{
		size.w = pkImage->GetWidth();
		size.h = pkImage->GetHeight();
	}

	return size;
}

void cgGdiplusRender::DrawImage( cgID image, const cgRectF& srcRect, const cgRectF & destRect )
{
	Gdiplus::Image * pkImage = m_kImageStorage.Find(image);
	if (pkImage)
	{
		Gdiplus::Rect kClipRect(destRect.x, destRect.y, destRect.w, destRect.h);
		m_pkGraphics->DrawImage(pkImage, kClipRect,
		srcRect.x, srcRect.y, srcRect.w, srcRect.h,
		Gdiplus::UnitPixel);
	}
}

void cgGdiplusRender::DrawLine( const cgPoint& from, const cgPoint& to, cgColor color )
{
	Gdiplus::Color penColor((Gdiplus::ARGB)color);

	Gdiplus::Pen pen(penColor);;

	m_pkGraphics->DrawLine(&pen, from.x, from.y, to.x, to.y);
}

void cgGdiplusRender::DrawBox( const cgRectF& rect, cgColor color )
{
	Gdiplus::Color penColor((Gdiplus::ARGB)color);

	Gdiplus::Pen pen(penColor);;

	m_pkGraphics->DrawRectangle(&pen, rect.x, rect.y, rect.w, rect.h);

}

void cgGdiplusRender::FillRect( const cgRectF& rect, cgColor color )
{
	Gdiplus::Color brushColor((Gdiplus::ARGB)color);

	Gdiplus::SolidBrush brush(brushColor);;

	m_pkGraphics->FillRectangle(&brush, rect.x, rect.y, rect.w, rect.h);
}

void cgGdiplusRender::DrawUIText( LPCTSTR lpctText, int nTextLen, 
	const cgRectF& rect, cgID font, int space , cgColor color, int style )
{
	Gdiplus::RectF kDrawRect (rect.x, rect.y, rect.w, rect.h);
	Gdiplus::StringFormat kFormat;

	if (style&DT_CENTER)
		kFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	if (style&DT_VCENTER)
		kFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	Gdiplus::Font * pkFont = FindFont(font);
	Gdiplus::SolidBrush brush(Gdiplus::Color((Gdiplus::ARGB)color));

	m_pkGraphics->DrawString(lpctText, nTextLen, pkFont,  kDrawRect, 
		&kFormat, &brush);
}

void cgGdiplusRender::DrawUIText( LPCTSTR lpctText, int nTextLen, 
	int x, int y, cgID font, cgColor color )
{
	Gdiplus::Font * pkFont = FindFont(font);
	Gdiplus::SolidBrush brush(Gdiplus::Color((Gdiplus::ARGB)color));
	Gdiplus::PointF point(x, y);

//	m_pkGraphics->DrawString(lpctText, nTextLen, pkFont, point, &brush);

	for (int i = 0; i < nTextLen; ++i)
	{
		m_pkGraphics->DrawString(lpctText+i, 1, pkFont, point, &brush);
		point.X += GetUICharWidth(lpctText[i], font);
	}
}

Gdiplus::Font * cgGdiplusRender::FindFont( cgID font )
{
	if (font < m_kFontList.size())
		return m_kFontList[font];

	return m_kFontList[0];
}

bool cgGdiplusRender::LoadFonts()
{
	unsigned uNum = GetPrivateProfileInt(TEXT("Fonts"), TEXT("Num"), 0, TEXT("./Fonts/Fonts.ini") );

	if (uNum <= 0)
		return false;

	cgFontConfig kConfig;
	TCHAR szAppName[CG_SHORT_TEXT_BUFF_LEN];
	for (unsigned i = 0; i < uNum; ++i)
	{
		cgSprintf(szAppName, CG_SHORT_TEXT_BUFF_LEN, TEXT("Font_%d"), i);

		kConfig.uSize = GetPrivateProfileInt(szAppName, TEXT("Size"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uHeight = GetPrivateProfileInt(szAppName, TEXT("Height"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uWidth = GetPrivateProfileInt(szAppName, TEXT("Width"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uWeight = GetPrivateProfileInt(szAppName, TEXT("Weight"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uMipLevels = GetPrivateProfileInt(szAppName, TEXT("MipLevels"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uItalic =  GetPrivateProfileInt(szAppName, TEXT("Italic"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uCharSet =  GetPrivateProfileInt(szAppName, TEXT("CharSet"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uOutputPrecision =  GetPrivateProfileInt(szAppName, TEXT("OutputPrecision"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uQuality =  GetPrivateProfileInt(szAppName, TEXT("Quality"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uPitchAndFamily = GetPrivateProfileInt(szAppName, TEXT("PitchAndFamily"), 0, TEXT("./Fonts/Fonts.ini"));

		GetPrivateProfileString(szAppName, TEXT("FaceName"), TEXT(""),
			kConfig.szFaceName, CG_SHORT_TEXT_BUFF_LEN, TEXT("./Fonts/Fonts.ini"));

		GetPrivateProfileString(szAppName, TEXT("Text"), TEXT(""),
			kConfig.szText, CG_SHORT_TEXT_BUFF_LEN, TEXT("./Fonts/Fonts.ini"));

		GetPrivateProfileString(szAppName, TEXT("Pic"), TEXT(""),
			kConfig.szPicPath, CG_SHORT_TEXT_BUFF_LEN, TEXT("./Fonts/Fonts.ini"));

		// 坑，如果width和height为零，则认为其大小和size一致 [3/11/2014 Administrator]
		if (kConfig.uSize == 0)
			kConfig.uSize = 12;

		if (kConfig.uWidth == 0)
			kConfig.uWidth = kConfig.uSize;

		if (kConfig.uHeight == 0)
			kConfig.uHeight = kConfig.uSize;

		Gdiplus::Font * pkFont = new Gdiplus::Font(kConfig.szFaceName, kConfig.uSize, 0, Gdiplus::UnitPixel);

		m_kFontList.push_back(pkFont);
	}

	return !m_kFontList.empty();
}

int cgGdiplusRender::GetUICharWidth( TCHAR ch, cgID idFont )
{
	int nW = 0;
	Gdiplus::Font * pkFont = FindFont(idFont);
	if (pkFont)
	{
		int nSize = pkFont->GetSize(); 

		if (ch < 128)
			nW = nSize/2;
		else
			nW = nSize;
	}
	return nW;
}


cgSizeF cgGdiplusRender::GetUICharSize( TCHAR ch, cgID idFont )
{
	Gdiplus::Font * pkFont = FindFont(idFont);
	if (pkFont)
	{
		int w = ch<128?pkFont->GetSize()/2:pkFont->GetSize();
		return cgSizeF(w, pkFont->GetSize());
	}
	return cgSizeF();
}

// --------------------------------------------------------------------------------------------------------------

cgUISurface * cgGdiplusRender::CreateUISurface( int w, int h, int nOpertion /*= 0*/ )
{
	return new cgGdiplusUISurface(m_hWnd, w, h);
}

bool cgGdiplusRender::PresentUISurface( cgUISurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect )
{
	// 清空背景为纯黑
	m_pkGraphics->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(0xff000000)), 
		destRect.x, destRect.y, destRect.w, destRect.h);

	// 混合
	::BitBlt((HDC)m_pkBkSurface->GetContent(), 
		destRect.x, destRect.y, destRect.w, destRect.h,
		(HDC)pkSurface->GetContent(), srcRect.x, srcRect.y, SRCPAINT);

	return true;
}

// ------------------------------------------------------------------------------------------------------

HBITMAP cgGdiplusRender::CreateDIBBitmap( int w, int h )
{
	BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
	int nBytesPerLine = ((w * 32 + 31) & (~31)) >> 3;
	stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
	stBmpInfoHeader.biWidth = w;   
	stBmpInfoHeader.biHeight = h;   
	stBmpInfoHeader.biPlanes = 1;
	stBmpInfoHeader.biBitCount = 32;   
	stBmpInfoHeader.biCompression = BI_RGB;   
	stBmpInfoHeader.biClrUsed = 0;   
	stBmpInfoHeader.biSizeImage = nBytesPerLine * h;

	PUINT32 pvBits = NULL;
	return ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (LPVOID*)&pvBits, NULL, 0);
}


Gdiplus::Image * cgGdiplusRender::LoadImageFromResource( UINT nID, LPCTSTR sTR )
{
	HINSTANCE hInst = GetModuleHandle( NULL);;
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),sTR); // type
	if (!hRsrc)
		return NULL;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return NULL;

	Gdiplus::Image * pkImage = LoadImageFromMemory(lpRsrc, len);

	FreeResource(lpRsrc);

	return pkImage;
}

Gdiplus::Image * cgGdiplusRender::LoadImageFromFile( LPCTSTR lpctPath )
{
	HANDLE hFile = CreateFile(lpctPath, GENERIC_READ, 0, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	BYTE * pBuff = NULL;
	Gdiplus::Image * pkImage = NULL;

	do 
	{
		DWORD dwLen = GetFileSize(hFile, NULL);
		if (dwLen <= 0)
			break;

		pBuff = new BYTE[dwLen];

		DWORD dwReadLen = 0;
		BOOL bRet = ReadFile(hFile, pBuff, dwLen, &dwReadLen, NULL);
		if (!bRet || dwReadLen <= 0)
			break;

		pkImage = LoadImageFromMemory(pBuff, dwReadLen);

	} while (false);

	if (pBuff)
		delete[] pBuff;
	CloseHandle(hFile);

	return pkImage;
}

Gdiplus::Image * cgGdiplusRender::LoadImageFromMemory( void * pBuff, int nLen )
{
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, nLen);
	BYTE* pmem = (BYTE*)GlobalLock(hMem);
	memcpy(pmem,pBuff,nLen);
	IStream* pstm;
	CreateStreamOnHGlobal(hMem,FALSE,&pstm);

	// load from stream
	Gdiplus::Image * pkImage =Gdiplus::Image::FromStream(pstm);

	// free/release stuff
	GlobalUnlock(hMem);
	pstm->Release();

	return pkImage;
}


// -----------------------------------------------------------------------------------
cgGdiplusUISurface::cgGdiplusUISurface( cgHwnd hWnd, int w, int h )
{
	m_hBitmap = cgGdiplusRender::CreateDIBBitmap(w, h);

	HDC hTempDC= ::GetDC(hWnd);
	m_hBitmapDC = CreateCompatibleDC(hTempDC);

	SelectObject(m_hBitmapDC, m_hBitmap);

	::ReleaseDC(hWnd, hTempDC);
}

cgGdiplusUISurface::~cgGdiplusUISurface()
{
	if (m_hBitmapDC)
		DeleteDC(m_hBitmapDC);

	if (m_hBitmap)
		DeleteObject(m_hBitmap);

}

void * cgGdiplusUISurface::GetContent()
{
	return (void*)m_hBitmapDC;
}

bool cgGdiplusUISurface::ReleaseContent( void * pContent )
{
	// 什么都不做了。
	return true;
}

int cgGdiplusUISurface::GetType()
{
	return 0;
}




