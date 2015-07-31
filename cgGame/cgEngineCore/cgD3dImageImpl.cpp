#include "StdAfx.h"
#include "cgD3dImageImpl.h"


cgD3DImageFromFile::cgD3DImageFromFile( LPDIRECT3DDEVICE9 lpDevice, LPCTSTR lpctFilePath )
{
	m_lpDevice = lpDevice;
	m_lpTex = NULL;
	m_strFilePath = lpctFilePath;

	D3DXIMAGE_INFO kInfo;
	D3DXGetImageInfoFromFile(m_strFilePath.c_str(), &kInfo);
	m_nWidth = kInfo.Width;
	m_nHeight = kInfo.Height;

	m_bIsLoaded = false;

	DoLoad();
}

cgD3DImageFromFile::~cgD3DImageFromFile()
{
	if (m_lpTex)
	{
		m_lpTex->Release();
		m_lpTex = NULL;
	}
}

bool cgD3DImageFromFile::OnLostDevice()
{
	if (m_lpTex)
	{
		m_lpTex->Release();
		m_lpTex = NULL;
	}
	m_bIsLoaded = false;

	return true;
}

bool cgD3DImageFromFile::OnResetDevice()
{
	DoLoad();

	return true;
}
void cgD3DImageFromFile::DoLoad()
{
	HRESULT hr = D3DXCreateTextureFromFileEx(m_lpDevice, m_strFilePath.c_str(),m_nWidth, m_nHeight,
		D3DFMT_FROM_FILE, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, 
		D3DX_FILTER_NONE, 
		D3DX_DEFAULT, NULL, NULL, NULL, &m_lpTex);

	OnImageLoaded(0);
}

void cgD3DImageFromFile::OnImageLoaded(int nResult)
{
	m_bIsLoaded = true;
}

LPDIRECT3DTEXTURE9 cgD3DImageFromFile::GetTexture()
{
	if (!m_lpTex)
		DoLoad();

	return m_lpTex;
}

// -----------------------------------------------------------------------------------------

cgD3DImageFromCreation::cgD3DImageFromCreation( LPDIRECT3DDEVICE9 lpDevice, int w, int h )
{
	m_lpDevice = lpDevice;
	m_lpTex = NULL;
	m_nWidth = w;
	m_nHeight = h;
	DoCreate();
}

cgD3DImageFromCreation::~cgD3DImageFromCreation()
{
	if (m_lpTex)
	{
		m_lpTex->Release();
		m_lpTex = NULL;
	}
}

bool cgD3DImageFromCreation::OnLostDevice()
{
	if (m_lpTex)
	{
		m_lpTex->Release();
		m_lpTex = NULL;
	}
	return true;
}

bool cgD3DImageFromCreation::OnResetDevice()
{
	return DoCreate();
}

bool cgD3DImageFromCreation::DoCreate()
{
	if (FAILED(m_lpDevice->CreateTexture(m_nWidth, m_nHeight, 0, 
		D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT, &m_lpTex, NULL)))
		return false;

	return true;
}
