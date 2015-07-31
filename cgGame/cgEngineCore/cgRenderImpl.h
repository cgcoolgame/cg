#ifndef cgRenderImpl_h__
#define cgRenderImpl_h__
#include "cgDefine.h"

class cgRenderSurface;

class cgRenderImpl
{
public:
	// 析构函数
	virtual ~cgRenderImpl(void){};

	// 初始化
	virtual bool Initialize(cgHwnd hWnd, int nWidth, int nHeight) = NULL;

	// 重新设置大小
	virtual bool Resize(int nWidth, int nHeight) = NULL;

	// 设置设置视口区
	virtual bool SetViewPort(const cgRectF& rect) = NULL;
	virtual void GetViewPort(cgRectF& rect) = NULL;

	// 清空背景
	virtual void ClearBack(cgColor color) = NULL;

	// 清空一个矩形
	virtual void ClearRect(const cgRectF& clearRect) = NULL;

	// 开启绘制
	virtual void BeginRender() = NULL;

	// 结束绘制
	virtual void EndRender() = NULL;

	// 显示到屏幕
	virtual void Present() = NULL;
// -------------------------------------------------------------------------------------
	// 设置环境光
	virtual void SetAmbientLight(cgColor light) = NULL;
	virtual cgColor GetAmbientLight() = NULL;

	// 开启牛逼的绘制模式，不常用！
	virtual void EnableTextureFilter(bool bEnable) = NULL;
// -------------------------------------------------------------------------------------

	// 加载纹理
	virtual cgID LoadTexture(LPCTSTR lpctPath, int nOpertion = NULL) = NULL;

	// 释放纹理
	virtual bool ReleaseTexture(cgID idTex) = NULL;

	// 创建可以后台渲染的贴图
	virtual cgID CreateTexture(int nWidth, int nHeight) = NULL;

	// 获取纹理大小
	virtual cgSize GetTextureSize(cgID idTex) = NULL;

	// 渲染纹理
	virtual void RenderTexture(cgID idTex, 
		const cgRectF& srcRect, 
		const cgRectF& destRect,
		cgColor color) = NULL;
// -------------------------------------------------------------------------------------
	// 绘制多边形
	virtual void RenderPolygon(const cgRenderVertex* pkVertexList, unsigned uVertexNum,
		cgID idTex) = NULL;

	// 填充矩形
	virtual void FillRect(const cgRectF& destRect, cgColor color) = NULL;

	// 绘制线框
	virtual void DrawBox(const cgRectF& destRect, cgColor color) = NULL;

	// 绘制直线
	virtual void DrawLine(const cgPoint& fromPoint, const cgPoint& toPoint, 
		cgColor color) = NULL;

	// 绘制点
	virtual void DrawPoint(const cgPoint& point, cgColor color) = NULL;
// -------------------------------------------------------------------------------------
	// 添加一种字体
	virtual cgID AddFont(const cgFontConfig& kConfig) = NULL;
	// 绘制文字
	virtual void RenderTextDirectly(LPCTSTR lpctText, int nTextLen, 
		const cgRectF& destRect, unsigned uFontID = 0, 
		cgColor color = 0xffffffff,
		unsigned uTextStyle = DT_CENTER|DT_VCENTER) = NULL;

	// 获取字符串宽度
	virtual int CalcTextWidth(LPCTSTR lpctText, int nTextLen, cgID font, 
		int nMaxWidth = 0x0fffffff, int nMaxHeight = 0x0fffffff) = NULL; 
// -------------------------------------------------------------------------------------
	// 设置临时渲染目标
	virtual bool PushRenderTarget(cgID idTex) = NULL;

	// 重置渲染目标
	virtual bool PopRenderTarget() = NULL;

	// 立即显示所有绘制结果
	virtual void SetRenderDirty() = NULL;

// -------------------------------------------------------------------------------------

	// 创建一个可供渲染的表面
	virtual cgRenderSurface * CreateRenderSurface(int w, int h, int nOpertion = 0) = NULL;

	// 显示表面
	virtual	bool PresentRenderSurface(cgRenderSurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect) = NULL;
// -------------------------------------------------------------------------------------
	// 截图
	virtual void ScreenShot(LPCTSTR lpctSavePath, cgScreenShotImageFormat enmFormat) = NULL;

};

#endif // cgRenderImpl_h__
