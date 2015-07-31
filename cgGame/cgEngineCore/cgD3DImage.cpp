#include "StdAfx.h"
#include "cgD3DImage.h"
#include "cgD3dImageImpl.h"

int cgD3DImage::GetWidth()
{
	return m_nWidth;
}

int cgD3DImage::GetHeight()
{
	return m_nHeight;
}


LPDIRECT3DTEXTURE9 cgD3DImage::GetTexture()
{
	return m_lpTex;
}

// -------------------------------------------------------------------------------------------------

cgD3DImage * cgD3DImage::LoadImage( LPDIRECT3DDEVICE9 lpDevice, LPCTSTR lpctPath )
{
	D3DXIMAGE_INFO kInfo;
	if (D3DXGetImageInfoFromFile(lpctPath, &kInfo) == D3D_OK)
		return new cgD3DImageFromFile(lpDevice, lpctPath);

	return NULL;
}

cgD3DImage * cgD3DImage::CreateImage( LPDIRECT3DDEVICE9 lpDevice, int nWidth, int nHeight )
{
	return new cgD3DImageFromCreation(lpDevice, nWidth, nHeight);
}

bool cgD3DImage::FreeImage( cgD3DImage * pkImage )
{
	delete pkImage;
	return true;
}
