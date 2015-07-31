
#ifndef cgUIRender_h__
#define cgUIRender_h__
#include "cgUIDef.h"

enum cgUIImageSurfaceType
{
	cgUIImageSurfaceTypeNone = 0,		// 无效的
	cgUIImageSurfaceTypeGdiplus = 1,	// gdiplus
	cgUIImageSurfaceTypeD3D = 2,		// d3d
};

class cgUISurface
{
public:
	cgUISurface(){}
	virtual ~cgUISurface(){}

	virtual void * GetContent() = NULL;
	virtual bool ReleaseContent(void * pContent) = NULL;
	virtual int GetType() = NULL;
};

class cgUIRender
{
public:
	cgUIRender(void);
	virtual ~cgUIRender(void);
	
	// 初始化
	virtual bool Initialize(cgHwnd hWnd, int w, int h);

	// 设置剪切矩形，push是与的关系，就是在pop之前，剪切区域只会越来越小，不能变大
	virtual bool PushClipRect(const cgRectF& clipRect) = NULL;
	virtual void PopClipRect() = NULL;

	// 清空一个矩形，清空为完全透明
	virtual void ClearRect(const cgRectF& rect) = NULL;

	// 开始绘制
	virtual void BeginRender() = NULL;
	virtual void EndRender() = NULL;
	virtual void Display() = NULL;

	//当大小发生变化
	virtual bool OnSizeChanged(int w, int h) = 0;
	// 加载图片
	virtual cgID LoadImage(LPCTSTR path)= NULL;
	virtual cgID LoadImage(cgID resID)= NULL;
	virtual bool ReleaseImage(cgID image) = NULL;

	// 获取图片的尺寸
	virtual cgSize GetImageSize(cgID image) = NULL;

	// 绘制
	virtual void DrawImage(cgID image, const cgRectF& srcRect, const cgRectF & destRect) = NULL;

	virtual void DrawLine(const cgPoint& from, const cgPoint& to, cgColor color) = NULL;

	virtual void DrawBox(const cgRectF& rect, cgColor color) = NULL;

	virtual void FillRect(const cgRectF& rect, cgColor color) = NULL;

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen,
		const cgRectF& rect, cgID font, int space , cgColor color, int style) = NULL;

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen, 
		int x, int y, cgID font, cgColor color) = NULL;

	// 创建一个可供渲染的表面
	virtual cgUISurface * CreateUISurface(int w, int h, int nOpertion = 0) = NULL;

	// 显示表面
	virtual bool PresentUISurface(cgUISurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect) = NULL;

	// 获取单个ch的宽度
	virtual int GetUICharWidth(TCHAR ch, cgID idFont) = NULL;

	// 获取单个ch的size
	virtual cgSizeF GetUICharSize(TCHAR ch, cgID idFont) = NULL;
public:
	static cgUIRender * GetRender();
private:
	static cgUIRender * ms_pkRender;

protected:
	cgHwnd m_hWnd;
	int m_nWidth;
	int m_nHeight;
};

#endif // cgUIRender_h__
