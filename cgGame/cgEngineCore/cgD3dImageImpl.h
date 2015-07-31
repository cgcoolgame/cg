
#ifndef cgD3dTextureImpl_h__
#define cgD3dTextureImpl_h__
#include "cgD3DImage.h"

// 从文件里面读取的贴图
class cgD3DImageFromFile:
	public cgD3DImage
{
public:
	cgD3DImageFromFile( LPDIRECT3DDEVICE9 lpDevice, LPCTSTR lpctFilePath);
	virtual ~cgD3DImageFromFile();

	virtual LPDIRECT3DTEXTURE9 GetTexture();

	virtual bool OnLostDevice();
	virtual bool OnResetDevice();

	// 当贴图完全加载上来的时候
	virtual void OnImageLoaded(int nResult);


private:

	void DoLoad();

private:
	
	cgString m_strFilePath;
	bool m_bIsLoaded;
};

// -----------------------------------------------------------------------------------------

// 直接创建的贴图
class cgD3DImageFromCreation:
	public cgD3DImage
{
public:
	cgD3DImageFromCreation(LPDIRECT3DDEVICE9 lpDevice, int w, int h);
	virtual ~cgD3DImageFromCreation();

	virtual bool OnLostDevice();
	virtual bool OnResetDevice();

private:
	bool DoCreate();

};
#endif // cgD3dTextureImpl_h__
