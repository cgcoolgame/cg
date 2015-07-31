
#ifndef cgGdiplusRender_h__
#define cgGdiplusRender_h__

#include "cgUIRender.h"
#include <GdiPlus.h>
#include "cgStorage.h"
#include <vector>
#include "cgSingleton.h"
#include <stack>

typedef std::vector<Gdiplus::Font*> GdiplusFontPtrList;

typedef cgStorage<Gdiplus::Image> cgGdiplusImageStorage;

class cgGdiplusUISurface:
	public cgUISurface
{
public:
	cgGdiplusUISurface(cgHwnd hWnd, int w, int h);
	virtual ~cgGdiplusUISurface();

public:
	virtual void * GetContent();
	virtual bool ReleaseContent(void * pContent);

	virtual int GetType();
private:
	HBITMAP m_hBitmap;
	HDC m_hBitmapDC;
};

class cgGdiplusRender :
	public cgUIRender,
	public cgSingleton<cgGdiplusRender>
{
public:
	cgGdiplusRender(void);
	~cgGdiplusRender(void);

	// 初始化
	virtual bool Initialize(cgHwnd hWnd, int w, int h);

	// 设置剪切矩形
	virtual bool PushClipRect(const cgRectF& clipRect);
	virtual void PopClipRect();
	virtual void ClearRect(const cgRectF& rect);

	// 绘制开关
	virtual void BeginRender();
	virtual void EndRender();
	virtual void Display();

	// 设置整体透明度
	virtual void SetAlpha(BYTE alpha);

	//当大小发生变化
	virtual bool OnSizeChanged(int w, int h);
	// 加载图片
	virtual cgID LoadImage(LPCTSTR path);
	virtual cgID LoadImage(cgID resID);
	virtual bool ReleaseImage(cgID image);

	virtual cgSize GetImageSize(cgID image);

	// 绘制
	virtual void DrawImage(cgID image, const cgRectF& srcRect, const cgRectF & destRect);

	virtual void DrawLine(const cgPoint& from, const cgPoint& to, cgColor color);

	virtual void DrawBox(const cgRectF& rect, cgColor color);

	virtual void FillRect(const cgRectF& rect, cgColor color);

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen,
		const cgRectF& rect, cgID font, int space , cgColor color, int style);

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen, 
		int x, int y, cgID font, cgColor color);

	// 创建一个可供渲染的表面
	cgUISurface * CreateUISurface(int w, int h, int nOpertion = 0) ;

	// 显示表面
	bool PresentUISurface(cgUISurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect) ;

	// 获取单个ch的宽度
	virtual int GetUICharWidth(TCHAR ch, cgID idFont) ;

	// 获取单个ch的size
	virtual cgSizeF GetUICharSize(TCHAR ch, cgID idFont);
public:

	static Gdiplus::Image * LoadImageFromResource(UINT nID, LPCTSTR sTR);
	static Gdiplus::Image * LoadImageFromFile(LPCTSTR lpctPath);
	static Gdiplus::Image * LoadImageFromMemory(void * pBuff, int nLen);

	static HBITMAP CreateDIBBitmap(int w, int h);

private:
	// 从资源读取图片信息

	// 找到字体
	Gdiplus::Font * FindFont(cgID font);

	// 加载字体
	bool LoadFonts();

	// 创建一个图片

private:
	cgUISurface * m_pkBkSurface;
	Gdiplus::Graphics *m_pkGraphics;

	BLENDFUNCTION m_kBlend;
	ULONG_PTR m_gdiplusToken;

	cgGdiplusImageStorage m_kImageStorage;
	GdiplusFontPtrList	m_kFontList;

	typedef std::stack<Gdiplus::Rect> ClipRectStack;
	ClipRectStack m_kClipRectStack;
};



#endif // cgGdiplusRender_h__
