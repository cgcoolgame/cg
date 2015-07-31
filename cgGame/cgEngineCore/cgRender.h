
#ifndef I2DRender_h__
#define I2DRender_h__
#include "cgSingleton.h"

/************************************************************************/
/* 下面是新的render结构，生命在于折腾，第N次了，每次都有新收获          */
/************************************************************************/

class cgRenderSurface
{
public:
	cgRenderSurface(){};
	virtual ~cgRenderSurface(){};
public:
	virtual void * GetContent() = NULL;
	virtual bool ReleaseContent(void * pContent) = NULL;
	virtual int GetType() = NULL;
};


class cgRenderImpl;

class cgRender:public cgSingleton<cgRender>
{
public:
	cgRender();
	virtual ~cgRender();
	
public:
	// 初始化
	bool Initialize(cgHwnd hWnd, int nWidth, int nHeight);

	// 重新设置大小
	bool Resize(int nWidth, int nHeight);

	// 设置设置视口区
	virtual bool SetViewPort(const cgRectF& rect);
	virtual void GetViewPort(cgRectF& rect);

	// 清空背景
	void ClearBack(cgColor color);

	// 清空一个矩形
	void ClearRect(const cgRectF& clearRect);

	// 渲染开关
	void BeginRender();
	void EndRender();

	// 显示到屏幕
	void Present();

// -------------------------------------------------------------------------------------

	// 设置环境光
	void SetAmbientLight(cgColor light);
	cgColor GetAmbientLight();
// -------------------------------------------------------------------------------------
	// 创建一个图片
	cgID LoadTexture(LPCTSTR lpctImagePath, int nOption = NULL);

	// 释放一个图片
	bool ReleaseTexture(cgID id);

	// 创建可以后台渲染的贴图
	cgID CreateTexture(int nWidth, int nHeight);

	// 获取图片尺寸
	cgSize GetTextureSize(cgID id);

// -------------------------------------------------------------------------------------
	void RenderTexture(cgID id, const cgRectF& srcRect, 
		const cgRectF& destRect,
		cgColor color);
	// 图元处理
	void FillRect(const cgRectF& destRect, cgColor color);

	// 绘制线框
	void DrawBox(const cgRectF& destRect, cgColor color);

	// 绘制直线
	void RenderLine(const cgPoint& fromPoint, const cgPoint& toPoint, 
		cgColor color);

	// 绘制点
	void RenderPoint(const cgPoint& point, cgColor color);

	// 绘制多边形，比较通用的函数
	void RenderPolygon(const cgRenderVertex* pkVertexList, unsigned uVertexNum,
		cgID idTexImage = CG_INVALID_ID);
// -------------------------------------------------------------------------------------
	// 获取单个ch的宽度
	int GetRenderCharWidth(TCHAR ch, cgID idFont);

	// 获取单个ch的宽度
	cgSizeF GetRenderCharSize(TCHAR ch, cgID idFont);

	// 测量字符串
	bool MeasureString(LPCTSTR text, int len, cgID font, 
		float & w, float & h, 
		float space, float scale);

	// 绘制文字,我才不管你怎么排版呢
	// 你让我从哪里开始绘制，我就从哪里绘制，哈哈哈哈！
	void RenderString(LPCTSTR lpctText, int nTextLen, 
		float x, float y, cgID font, cgColor color);

	// 好吧，我收回上面的话，render还是要管排版的
	void RenderString(LPCTSTR lpctText, int nTextLen,
		const cgRectF& rect, cgID font, float space , 
		cgColor color, unsigned style, float scale = 1.0f);
	
// -------------------------------------------------------------------------------------

	// 设置临时渲染目标
	bool PushRenderTarget(cgID id);

	// 重置渲染目标
	bool PopRenderTarget();

	// 立即显示所有绘制结果
	void SetRenderDirty();

// -------------------------------------------------------------------------------------

	// 创建一个可供渲染的表面
	cgRenderSurface * CreateRenderSurface(int w, int h, int nOpertion = 0) ;

	// 显示表面
	bool PresentRenderSurface(cgRenderSurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect);

// -------------------------------------------------------------------------------------

	// 截图
	void ScreenShot(LPCTSTR lpctSavePath, cgScreenShotImageFormat enmFormat);

// -------------------------------------------------------------------------------------
protected:
	cgRenderImpl	* m_pkRenderImpl;
};

#endif // I2DRender_h__
