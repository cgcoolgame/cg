#ifndef cgD3DImage_h__
#define cgD3DImage_h__
#include <d3d9.h>
#include <d3dx9core.h>

// d3dtextureµÄ·â×°

class cgD3DImage
{
public:
	virtual ~cgD3DImage(void){};

	int GetWidth() ;
	int GetHeight() ;

	virtual LPDIRECT3DTEXTURE9 GetTexture();

	virtual bool OnLostDevice() = NULL;
	virtual bool OnResetDevice() = NULL;

	static cgD3DImage * LoadImage(LPDIRECT3DDEVICE9 lpDevice, LPCTSTR lpctPath);
	static cgD3DImage * CreateImage(LPDIRECT3DDEVICE9 lpDevice, int nWidth, int nHeight);
	static bool FreeImage(cgD3DImage * pkImage);

protected:
	LPDIRECT3DDEVICE9 m_lpDevice;
	LPDIRECT3DTEXTURE9 m_lpTex;
	int m_nWidth;
	int m_nHeight;
};

#endif // cgD3DTexture_h__
