#include "StdAfx.h"
#include "cgD3DRenderImpl.h"
#include "cgD3dImageImpl.h"

D3DXIMAGE_FILEFORMAT cgImageFormatToDxFormat(cgScreenShotImageFormat cgFormat)
{
	switch(cgFormat)
	{
	case cgScreenShotImageFormat_BMP:
		return D3DXIFF_BMP;
		break;
	case cgScreenShotImageFormat_JPG:
		return D3DXIFF_JPG;
		break;
	case cgScreenShotImageFormat_TGA:
		return D3DXIFF_TGA;
		break;
	case cgScreenShotImageFormat_PNG:
		return D3DXIFF_PNG;
		break;
	case cgScreenShotImageFormat_DDS:
		return D3DXIFF_DDS;
		break;
	case cgScreenShotImageFormat_PPM:
		return D3DXIFF_PPM;
		break;
	case cgScreenShotImageFormat_DIB:
		return D3DXIFF_DIB;
		break;
	case cgScreenShotImageFormat_HDR:
		return D3DXIFF_HDR;
		break;
	case cgScreenShotImageFormat_PFM:
		return D3DXIFF_PFM;
		break;
	default:
		break;
	}

	return D3DXIFF_BMP;
}

// ---------------------------------------------------------------------------------------------
const DWORD tagD3DVertex::FVF = D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1;//|D3DFVF_DIFFUSE;


// ---------------------------------------------------------------------------------------------


cgD3DRenderImpl::cgD3DRenderImpl(void)
{
	m_lpD3D = NULL;
	m_lpDevice = NULL;
	m_lpVertexBuff = NULL;
	m_pkVertexData = NULL;
	m_uVertexDataOffset = 0;

	m_pRenderUnitList = NULL;
	m_uRenderUnitNum = 0;

	m_pkImageStorage = NULL;
	m_uAmbientLight = 0xffffffff;// 纯白色
}


cgD3DRenderImpl::~cgD3DRenderImpl(void)
{
	delete [] m_pRenderUnitList;

	delete m_pkImageStorage;

	if (m_lpVertexBuff)
		m_lpVertexBuff->Release();

	if ( m_lpDevice ) 
		m_lpDevice->Release ( ) ;

	if ( m_lpD3D )
		m_lpD3D->Release ( ) ;
}

// ---------------------------------------------------------------------------------------
bool cgD3DRenderImpl::Initialize( cgHwnd hWnd, int nWidth, int nHeight )
{
	m_lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_lpD3D)
		return false;

	ZeroMemory(&m_kPresentParams, sizeof(D3DPRESENT_PARAMETERS));
	m_kPresentParams.hDeviceWindow = hWnd;
	m_kPresentParams.Windowed = TRUE;
	m_kPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_kPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
	m_kPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	m_kPresentParams.BackBufferWidth = nWidth;
	m_kPresentParams.BackBufferHeight = nHeight;
//	kParams.EnableAutoDepthStencil = TRUE;
//	kParams.AutoDepthStencilFormat = D3DFMT_D24S8;

	HRESULT hr = m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING/*|D3DCREATE_MULTITHREADED*/,
		&m_kPresentParams,&m_lpDevice);
	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("Create D3D Render Failed !"), 0, 0);
		return false;
	}

	SetupRenderState();

	SetupTextureStageState();

	if (!CreateRenderBuffer())
		return false;

	m_pkImageStorage = new cgD3DImageStorage(CG_DEFAULT_STORED_TEXTURE_NUM);

	m_pRenderUnitList = new cgD3DRenderUnit[CG_DEFAULT_RENDER_UNIT_CACHE_NUM];

	return true;
}


bool cgD3DRenderImpl::Resize( int nWidth, int nHeight )
{
	if (nWidth > 0 && nHeight > 0 && 
		(nWidth != m_kPresentParams.BackBufferWidth || 
		nHeight != m_kPresentParams.BackBufferHeight))
	{
		m_kPresentParams.BackBufferWidth = nWidth;
		m_kPresentParams.BackBufferHeight = nHeight;

		PreOnLostDevice();
		// ------------------------------------------
		OnLostDevice();
		// ------------------------------------------
		OnResetDevice();
	}
	
	return true;
}


bool cgD3DRenderImpl::PreOnLostDevice()
{
	for (unsigned i = 0; i < m_pkImageStorage->Size(); ++i)
	{
		cgD3DImage * pkImage = m_pkImageStorage->Index(i);
		if (pkImage)
			pkImage->OnLostDevice();
	}

	for (unsigned i = 0; i < m_kFontList.size(); ++i)
	{
		LPD3DXFONT pkFont = m_kFontList[i];
		if (pkFont)
			pkFont->OnLostDevice();
	}

	m_lpDevice->SetStreamSource(0, NULL, 0, NULL);
	if (m_lpVertexBuff)
	{
		m_lpVertexBuff->Release();
		m_lpVertexBuff = NULL;
	}

	return true;
}


bool cgD3DRenderImpl::OnLostDevice()
{
	if (FAILED( m_lpDevice->Reset(&m_kPresentParams)))
	{
		MessageBoxA(m_kPresentParams.hDeviceWindow, "Device Reset Failed !", "Cool Game !", MB_OK);
		return false;
	}

	SetupRenderState();
	SetupTextureStageState();

	return true;
}

bool cgD3DRenderImpl::OnResetDevice()
{
	CreateRenderBuffer();
	for (unsigned i = 0; i < m_pkImageStorage->Size(); ++i)
	{
		cgD3DImage * pkImage = m_pkImageStorage->Index(i);
		if (pkImage)
			pkImage->OnResetDevice();
	}

	for (unsigned i = 0; i < m_kFontList.size(); ++i)
	{
		LPD3DXFONT pkFont = m_kFontList[i];
		if (pkFont)
			pkFont->OnResetDevice();
	}

	return true;
}

// --------------------------------------------------------------------------------------------------


bool cgD3DRenderImpl::CreateRenderBuffer()
{
	HRESULT hr = m_lpDevice->CreateVertexBuffer(
		CG_MAX_DXVERTEX_BUFFER_LEN*sizeof(cgD3DVertex), 0, cgD3DVertex::FVF,
		D3DPOOL_MANAGED, &m_lpVertexBuff, NULL);

	if (FAILED(hr))
		return false;

	m_lpDevice->SetStreamSource(0, m_lpVertexBuff, 0, sizeof(cgD3DVertex));
	m_lpDevice->SetFVF(cgD3DVertex::FVF);

	return true;
}

// --------------------------------------------------------------------------------------------------
void cgD3DRenderImpl::ClearBack( cgColor color )
{
	m_lpDevice->Clear(0, NULL, 
		D3DCLEAR_TARGET, color, 0.0f, 0);
}


void cgD3DRenderImpl::ClearRect( const cgRectF& clearRect )
{
	// 绘制单元加入缓存
	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Clear;
	unit._srcRect = clearRect;

}

void cgD3DRenderImpl::DoClearRect( const cgRectF & clearRect )
{
	D3DRECT rect = {clearRect.x, clearRect.y, clearRect.GetRight(), clearRect.GetBottom()};
	m_lpDevice->Clear(1, &rect, D3DCLEAR_TARGET, 0x00000000, 0.0f, 0);
}

// --------------------------------------------------------------------------------------------------

bool cgD3DRenderImpl::SetViewPort( const cgRectF& rect )
{
	// 绘制单元加入缓存
	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_ViewPort;
	unit._srcRect = rect;

	return true;
}

bool cgD3DRenderImpl::DoSetViewPort( const cgRectF& rect )
{
	D3DVIEWPORT9 viewPort = {rect.x, rect.y, rect.w, rect.h, 0.0f, 1.0f};

	return D3D_OK ==  m_lpDevice->SetViewport(&viewPort);
}


void cgD3DRenderImpl::GetViewPort( cgRectF& rect )
{
	D3DVIEWPORT9 viewPort;
	m_lpDevice->GetViewport(&viewPort);
	rect.Set(viewPort.X, viewPort.Y, viewPort.Width, viewPort.Height);
}

// --------------------------------------------------------------------------------------------------

void cgD3DRenderImpl::BeginRender()
{
	m_lpDevice->BeginScene();
	
	BeginCacheRenderUnits();
}

void cgD3DRenderImpl::EndRender()
{
	EndCacheRenderUnits();
	
	m_lpDevice->EndScene();
}

void cgD3DRenderImpl::Present()
{
	m_lpDevice->Present(NULL, NULL, NULL, NULL);

}

cgID cgD3DRenderImpl::LoadTexture( LPCTSTR lpctPath, int nOpertion /*= NULL*/ )
{
	cgD3DImage * pkImage = cgD3DImage::LoadImage(m_lpDevice, lpctPath);
	if (!pkImage)
		return CG_INVALID_ID;

	return m_pkImageStorage->Add(pkImage);

}

cgID cgD3DRenderImpl::CreateTexture( int nWidth, int nHeight )
{
	cgD3DImage * pkImage = cgD3DImage::CreateImage(m_lpDevice, nWidth, nHeight);
	if (!pkImage)
		return CG_INVALID_ID;

	return m_pkImageStorage->Add(pkImage);
}

bool cgD3DRenderImpl::ReleaseTexture( cgID idTex )
{
	cgD3DImage* pkImage = m_pkImageStorage->Remove(idTex);
	if (!pkImage)
		return false;

	return cgD3DImage::FreeImage(pkImage);
}

cgSize cgD3DRenderImpl::GetTextureSize( cgID idTex )
{
	cgSize imgSize;

	cgD3DImage * pkImage = m_pkImageStorage->Find(idTex);
	if (pkImage)
	{
		imgSize.w = pkImage->GetWidth();
		imgSize.h = pkImage->GetHeight();
	}
	
	return imgSize;
}


cgRenderSurface * cgD3DRenderImpl::CreateRenderSurface( int w, int h, int nOpertion /*= 0*/ )
{
	LPDIRECT3DSURFACE9 lpSurface = NULL;
	if (FAILED(m_lpDevice->CreateOffscreenPlainSurface(w, h, 
		D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &lpSurface, NULL)))
		return NULL;
	
	return (cgRenderSurface*)new cgDxRenderSurface(lpSurface);
}

bool cgD3DRenderImpl::PresentRenderSurface( cgRenderSurface * pkSurface, 
	const cgRectF& srcRect, const cgRectF& destRect )
{
	if (!pkSurface)
		return false;

	// 绘制单元加入缓存
	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Surface;
	unit._surface = ((cgDxRenderSurface*)pkSurface)->GetD3DSurface();
	unit._srcRect = srcRect;
	unit._destRect = destRect;
	unit._surface->AddRef();

	return true;
}


bool cgD3DRenderImpl::DoPresentRenderSurface( LPDIRECT3DSURFACE9 lpSurface, const cgRectF& srcRect, const cgRectF& destRect )
{
	LPDIRECT3DSURFACE9 lpBkBuff = NULL;
	if (FAILED(m_lpDevice->GetRenderTarget(0, &lpBkBuff)))
		return false;

	RECT rect = {srcRect.x, srcRect.y, srcRect.GetRight(), srcRect.GetBottom()};
	POINT point = {destRect.x, destRect.y};
	if (FAILED(m_lpDevice->UpdateSurface(lpSurface, &rect, lpBkBuff, &point)))
		return false;

	lpBkBuff->Release();
	lpSurface->Release();

	return true;
}

// --------------------------------------------------------------------------------

bool cgD3DRenderImpl::BeginCacheRenderUnits()
{
	m_pkVertexData = NULL;
	m_uVertexDataOffset = 0;
	m_uRenderUnitNum = 0;

	unsigned uDataLen =  CG_MAX_DXVERTEX_BUFFER_LEN*sizeof(cgD3DVertex);
	// 锁定所有的buffer
	if (FAILED(m_lpVertexBuff->Lock(0, uDataLen,
		(void**)&m_pkVertexData, 0)))
		return false;
	
	memset(m_pkVertexData, NULL, uDataLen);

	return true;
}

bool cgD3DRenderImpl::EndCacheRenderUnits()
{
	m_lpVertexBuff->Unlock();

	LPDIRECT3DTEXTURE9 lpLastTex = NULL;
	for (unsigned i = 0; i < m_uRenderUnitNum; ++i)
	{
		cgD3DRenderUnit & unit = m_pRenderUnitList[i];

		switch (unit._type)
		{
		case cgD3DRenderUnitType_Clear:
			{
				DoClearRect(unit._srcRect);
			}break;
		case cgD3DRenderUnitType_ViewPort:
			{
				DoSetViewPort(unit._srcRect);
			}break;
		case cgD3DRenderUnitType_Primitive:
			{
				if (lpLastTex != unit._tex)
				{
					lpLastTex = unit._tex;
					m_lpDevice->SetTexture(0, lpLastTex);
				}
				m_lpDevice->DrawPrimitive(unit._primitive, unit._offset, unit._count);
			}break;
		case cgD3DRenderUnitType_Surface:
			{
				DoPresentRenderSurface(unit._surface, unit._srcRect, unit._destRect);
			}break;
		default:
			break;
		}
	}
	m_lpDevice->SetTexture(0, NULL);
	m_uVertexDataOffset = 0;
	m_pkVertexData = NULL;

	return true;
}

void cgD3DRenderImpl::EnsureVertexDataEnough( unsigned uNeedLen )
{
	if (m_uVertexDataOffset+uNeedLen > CG_MAX_DXVERTEX_BUFFER_LEN
		|| m_uRenderUnitNum >= CG_DEFAULT_RENDER_UNIT_CACHE_NUM)
	{
		// 如果剩余的数据缓存不足，则把已经缓存的绘制出来，
		// 重新开始缓冲
		EndCacheRenderUnits();
		BeginCacheRenderUnits();
	}
}


// ------------------------------------------------------------------------------------
void cgD3DRenderImpl::RenderPolygon( const cgRenderVertex* pkVertexList, unsigned uVertexNum, 
	cgID idTex )
{
	EnsureVertexDataEnough(uVertexNum);

	cgD3DImage * pkImage = m_pkImageStorage->Find(idTex);
	if (!pkImage)
		return ;

	cgD3DVertex * pkVertexData = m_pkVertexData+m_uVertexDataOffset;
	for (unsigned i = 0; i < uVertexNum; ++i)
	{
		pkVertexData[i].x = pkVertexList[i].x;
		pkVertexData[i].y = pkVertexList[i].y;
		pkVertexData[i].u = pkVertexList[i].u;
		pkVertexData[i].v = pkVertexList[i].v;
		pkVertexData[i].color = pkVertexList[i].color&m_uAmbientLight;
		pkVertexData[i].rhw = 1.0f;
	}

	// 绘制单元加入缓存
	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Primitive;
	unit._primitive = D3DPT_TRIANGLEFAN;
	unit._offset = m_uVertexDataOffset;
	unit._count = uVertexNum-2;
	unit._tex = pkImage->GetTexture();

	m_uVertexDataOffset += uVertexNum;

#ifdef _DEBUG
	if (GetKeyState(VK_CONTROL) < 0)
	{
		cgPoint beginPoint;
		cgPoint endPoint;
		for (unsigned i = 0; i < uVertexNum; ++i)
		{
			beginPoint.x = pkVertexList[i].x;
			beginPoint.y = pkVertexList[i].y;
			endPoint.x = pkVertexList[(i+1)%uVertexNum].x;
			endPoint.y = pkVertexList[(i+1)%uVertexNum].y;

			DrawLine(beginPoint, endPoint, 0xffffffff);
		}
	}
#endif
}
void cgD3DRenderImpl::RenderTexture( cgID idTex, const cgRectF& srcRect, 
	const cgRectF& destRect, cgColor color )
{
	cgD3DImage* pkImage = m_pkImageStorage->Find(idTex);
	if (!pkImage)
		return ;

	color &= m_uAmbientLight;

	unsigned uNeedNum = CG_TEXTURE_NEED_VERTEX_NUM;
	EnsureVertexDataEnough(uNeedNum);

	cgD3DVertex * pkVertexData = m_pkVertexData+m_uVertexDataOffset;

	pkVertexData[0].x = static_cast<float>(destRect.x);
	pkVertexData[0].y = static_cast<float>(destRect.y);
	pkVertexData[0].u = (srcRect.x+0.5f)/pkImage->GetWidth();
	pkVertexData[0].v = (srcRect.y+0.5f)/pkImage->GetHeight();
	pkVertexData[0].color = color;
	pkVertexData[0].rhw = 1.0f;

	pkVertexData[1].x = static_cast<float>(destRect.x+destRect.w);
	pkVertexData[1].y = static_cast<float>(destRect.y);
	pkVertexData[1].u = (srcRect.x+srcRect.w+0.5f)/pkImage->GetWidth();
	pkVertexData[1].v = (srcRect.y+0.5f)/pkImage->GetHeight();
	pkVertexData[1].color = color;
	pkVertexData[1].rhw = 1.0f;

	pkVertexData[2].x = static_cast<float>(destRect.x+destRect.w);
	pkVertexData[2].y = static_cast<float>(destRect.y+destRect.h);
	pkVertexData[2].u = (srcRect.x+srcRect.w+0.5f)/pkImage->GetWidth();
	pkVertexData[2].v = (srcRect.y+srcRect.h+0.5f)/pkImage->GetHeight();
	pkVertexData[2].color = color;
	pkVertexData[2].rhw = 1.0f;

	pkVertexData[3].x = static_cast<float>(destRect.x);
	pkVertexData[3].y = static_cast<float>(destRect.y+destRect.h);
	pkVertexData[3].u = (srcRect.x+0.5f)/pkImage->GetWidth();
	pkVertexData[3].v = (srcRect.y+srcRect.h+0.5f)/pkImage->GetHeight();
	pkVertexData[3].color = color;
	pkVertexData[3].rhw = 1.0f;

	// 绘制单元加入缓存
	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Primitive;
	unit._primitive = D3DPT_TRIANGLEFAN;
	unit._offset = m_uVertexDataOffset;
	unit._count = 2;
	unit._tex = pkImage->GetTexture();

	m_uVertexDataOffset += uNeedNum;

#ifdef _DEBUG
	if (GetKeyState(VK_CONTROL) < 0)
	{
		DrawBox(destRect, 0xffffffff);
	}
#endif
}

void cgD3DRenderImpl::FillRect( const cgRectF& destRect, cgColor color )
{
	unsigned uNeedNum = CG_RECT_NEED_VERTEX_NUM;
	EnsureVertexDataEnough(uNeedNum);

	cgD3DVertex * pkVertexData = m_pkVertexData+m_uVertexDataOffset;

	pkVertexData[0].x = static_cast<float>(destRect.x);
	pkVertexData[0].y = static_cast<float>(destRect.y);
	pkVertexData[0].color = color;
	pkVertexData[0].rhw = 1.0f;

	pkVertexData[1].x = static_cast<float>(destRect.x+destRect.w);
	pkVertexData[1].y = static_cast<float>(destRect.y);
	pkVertexData[1].color = color;
	pkVertexData[1].rhw = 1.0f;

	pkVertexData[2].x = static_cast<float>(destRect.x+destRect.w);
	pkVertexData[2].y = static_cast<float>(destRect.y+destRect.h);
	pkVertexData[2].color = color;
	pkVertexData[2].rhw = 1.0f;

	pkVertexData[3].x = static_cast<float>(destRect.x);
	pkVertexData[3].y = static_cast<float>(destRect.y+destRect.h);
	pkVertexData[3].color = color;
	pkVertexData[3].rhw = 1.0f;

	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Primitive;
	unit._primitive = D3DPT_TRIANGLEFAN;
	unit._offset = m_uVertexDataOffset;
	unit._count = 2;
	unit._tex = NULL;

	m_uVertexDataOffset += uNeedNum;
}

void cgD3DRenderImpl::DrawBox( const cgRectF& destRect, cgColor color )
{
	unsigned uNeedNum = CG_BOX_NEED_VERTEX_NUM;
	EnsureVertexDataEnough(uNeedNum);

	cgD3DVertex * pkVertexData = m_pkVertexData+m_uVertexDataOffset;

	pkVertexData[0].x = static_cast<float>(destRect.x);
	pkVertexData[0].y = static_cast<float>(destRect.y);
	pkVertexData[0].color = color;
	pkVertexData[0].rhw = 1.0f;

	pkVertexData[1].x = static_cast<float>(destRect.x+destRect.w);
	pkVertexData[1].y = static_cast<float>(destRect.y);
	pkVertexData[1].color = color;
	pkVertexData[1].rhw = 1.0f;

	pkVertexData[2].x = static_cast<float>(destRect.x+destRect.w);
	pkVertexData[2].y = static_cast<float>(destRect.y+destRect.h);
	pkVertexData[2].color = color;
	pkVertexData[2].rhw = 1.0f;

	pkVertexData[3].x = static_cast<float>(destRect.x);
	pkVertexData[3].y = static_cast<float>(destRect.y+destRect.h);
	pkVertexData[3].color = color;
	pkVertexData[3].rhw = 1.0f;

	pkVertexData[4].x = static_cast<float>(destRect.x);
	pkVertexData[4].y = static_cast<float>(destRect.y);
	pkVertexData[4].color = color;
	pkVertexData[4].rhw = 1.0f;

	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Primitive;
	unit._primitive = D3DPT_LINESTRIP;
	unit._offset = m_uVertexDataOffset;
	unit._count = 4;
	unit._tex = NULL;

	m_uVertexDataOffset += uNeedNum;
}

void cgD3DRenderImpl::DrawLine( const cgPoint& fromPoint, const cgPoint& toPoint, 
	cgColor color )
{
	unsigned uNeedNum = CG_LINE_NEED_VERTEX_NUM;
	EnsureVertexDataEnough(uNeedNum);

	cgD3DVertex * pkVertexData = m_pkVertexData+m_uVertexDataOffset;

	pkVertexData[0].x = static_cast<float>(fromPoint.x);
	pkVertexData[0].y = static_cast<float>(fromPoint.y);
	pkVertexData[0].color = color;
	pkVertexData[0].rhw = 1.0f;

	pkVertexData[1].x = static_cast<float>(toPoint.x);
	pkVertexData[1].y = static_cast<float>(toPoint.y);
	pkVertexData[1].color = color;
	pkVertexData[1].rhw = 1.0f;

	// 绘制单元加入缓存
	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Primitive;
	unit._primitive = D3DPT_LINELIST;
	unit._offset = m_uVertexDataOffset;
	unit._count = 1;
	unit._tex = NULL;

	m_uVertexDataOffset += uNeedNum;
}

void cgD3DRenderImpl::DrawPoint( const cgPoint& point, cgColor color )
{
	unsigned uNeedNum = CG_POINT_NEED_VERTEX_NUM;
	EnsureVertexDataEnough(uNeedNum);

	cgD3DVertex * pkVertexData = m_pkVertexData+m_uVertexDataOffset;

	pkVertexData[0].x = static_cast<float>(point.x);
	pkVertexData[0].y = static_cast<float>(point.y);
	pkVertexData[0].color = color;
	pkVertexData[0].rhw = 1.0f;

	// 绘制单元加入缓存
	cgD3DRenderUnit & unit = m_pRenderUnitList[m_uRenderUnitNum++];
	unit._type = cgD3DRenderUnitType_Primitive;
	unit._primitive = D3DPT_POINTLIST;
	unit._offset = m_uVertexDataOffset;
	unit._count = 1;
	unit._tex = NULL;

	m_uVertexDataOffset += uNeedNum;
}


int cgD3DRenderImpl::CalcTextWidth( LPCTSTR lpctText, int nTextLen,
	cgID font, int nMaxWidth /*= 0x0fffffff*/, int nMaxHeight )
{
	LPD3DXFONT lpFont = FindFont(font);
	if (lpFont)
	{
		RECT kRect = {0, 0, nMaxWidth, nMaxHeight};
		lpFont->DrawText(NULL, lpctText, nTextLen, 
			&kRect, DT_CALCRECT, 0xffffffff);

		return kRect.right;
	}

	return 0;
}


void cgD3DRenderImpl::RenderTextDirectly(LPCTSTR lpctText, int nTextLen, 
	const cgRectF& destRect, unsigned uFontID /*= 0*/, 
	cgColor color /*= 0xffffffff*/,
	unsigned uTextStyle/* = DT_CENTER|DT_VCENTER*/ )
{
	LPD3DXFONT lpFont = FindFont(uFontID);
	if (lpFont)
	{
		RECT kRect = {destRect.x, destRect.y, destRect.x+destRect.w, destRect.y+destRect.h};
		lpFont->DrawText(NULL, lpctText, nTextLen, 
			&kRect, uTextStyle, color);
	}
}


bool cgD3DRenderImpl::PushRenderTarget( cgID idTex )
{
	SetRenderDirty();

	cgD3DImage * pkImage = m_pkImageStorage->Find(idTex);
	if (!pkImage)
		return false;

	LPDIRECT3DTEXTURE9  lpTex = pkImage->GetTexture();
	if (!lpTex)
		return false;

	LPDIRECT3DSURFACE9 lpNewSurface;
	if (FAILED(lpTex->GetSurfaceLevel(0, &lpNewSurface)))
		return false;

	cgRenderTargetMemo memo;
	if (FAILED(m_lpDevice->GetViewport(&memo.viewPort)))
		return false;

	if (FAILED(m_lpDevice->GetRenderTarget(0, &memo.surface)))
		return false;
		
	if (FAILED(m_lpDevice->SetRenderTarget(0, lpNewSurface)))
		return false;

	lpNewSurface->Release();

	m_kRenderTargetStack.push(memo);

	return true;
}

bool cgD3DRenderImpl::PopRenderTarget()
{
	SetRenderDirty();
	// 如果保存的target为空，说明需要重置
	if (m_kRenderTargetStack.empty())
		return false;

	cgRenderTargetMemo memo = m_kRenderTargetStack.top();
	m_kRenderTargetStack.pop();

	m_lpDevice->SetRenderTarget(0, memo.surface);
	m_lpDevice->SetViewport(&memo.viewPort);
	memo.surface->Release();

	return true;
}

void cgD3DRenderImpl::SetRenderDirty()
{
	EndCacheRenderUnits();
	BeginCacheRenderUnits();
}

void cgD3DRenderImpl::ScreenShot( LPCTSTR lpctSavePath,
	cgScreenShotImageFormat enmFormat )
{
	IDirect3DSurface9 * pkBackBuff = NULL;
	HRESULT hr = m_lpDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pkBackBuff);
	if (FAILED(hr))
		return ;

	D3DXSaveSurfaceToFile(lpctSavePath, cgImageFormatToDxFormat(enmFormat),
		pkBackBuff, NULL, NULL);

	pkBackBuff->Release();
}


LPDIRECT3DDEVICE9 cgD3DRenderImpl::GetDevice()
{
	return m_lpDevice;
}


LPD3DXFONT cgD3DRenderImpl::FindFont( cgID id )
{
	if (id < m_kFontList.size())
	{
		return m_kFontList[id];
	}
	return m_kFontList[0];
}

cgID cgD3DRenderImpl::AddFont( const cgFontConfig& kConfig )
{
	LPD3DXFONT lpFont = NULL;
	if ( FAILED(D3DXCreateFont(m_lpDevice, kConfig.uSize, 0 /*kConfig.uWidth*/,
		kConfig.uWeight, kConfig.uMipLevels, kConfig.uItalic, kConfig.uCharSet, 
		kConfig.uOutputPrecision, kConfig.uQuality, kConfig.uPitchAndFamily,
		kConfig.szFaceName, &lpFont) ) )
		return CG_INVALID_ID;

	m_kFontList.push_back(lpFont);

	// 因为id是这么用的：m_kFontList[id]
	// 所以返回的是他的索引
	return m_kFontList.size()-1;
}

void cgD3DRenderImpl::EnableTextureFilter( bool bEnable )
{
	if (bEnable)
	{
		m_lpDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		m_lpDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	}else
	{
		m_lpDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		m_lpDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	}
}

void cgD3DRenderImpl::SetAmbientLight( cgColor light )
{
	m_uAmbientLight = light;
}

cgColor cgD3DRenderImpl::GetAmbientLight()
{
	return m_uAmbientLight;
}

void cgD3DRenderImpl::SetupRenderState()
{
	m_lpDevice->SetRenderState(D3DRS_LIGHTING, false);
	//	m_pkD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_lpDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ## alpha 混合
	m_lpDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ## alpha 混合

	//	m_pkD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);		// 颜色混合
	//	m_pkD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);	// 颜色混合

	//	m_lpDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//	m_lpDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
}

void cgD3DRenderImpl::SetupTextureStageState()
{
	m_lpDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );  
	m_lpDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );  
	m_lpDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE ); 
}


// -----------------------------------------------------------------------------------------


cgDxRenderSurface::cgDxRenderSurface( LPDIRECT3DSURFACE9 lpSurface )
{
	m_lpSurface = lpSurface;
}

cgDxRenderSurface::~cgDxRenderSurface()
{
	if (m_lpSurface)
		m_lpSurface->Release();
}

void* cgDxRenderSurface::GetContent()
{
	HDC hdc;
	if (!m_lpSurface || FAILED(m_lpSurface->GetDC(&hdc)))
		return NULL;

	return (void*)hdc;
}

bool cgDxRenderSurface::ReleaseContent( void * pContent )
{
	if (!pContent || !m_lpSurface)
		return false;

	return m_lpSurface->ReleaseDC((HDC)pContent) == S_OK;
}

int cgDxRenderSurface::GetType()
{
	return 0;
}

LPDIRECT3DSURFACE9 cgDxRenderSurface::GetD3DSurface()
{
	return m_lpSurface;
}
