////////////////////////////////////////////////
//	FileName:		cgDxRenderImp.h
//	Author:			Master
//	Date:			2014.03.8
//	Description:	d3d 的render的再一次封装，第N次，但绝对不是最后一次
//	mark:			每天进步一点点
////////////////////////////////////////////////

#ifndef cgDxRenderImp_h__
#define cgDxRenderImp_h__

#include <d3d9.h>
#include <d3dx9core.h>
#include <vector>
#include "cgrenderimpl.h"
#include "cgStorage.h"
#include <stack>
#include "cgRender.h"
#include "cgD3DImage.h"

// 预分配的顶点的数量:1000个矩形左右，够用了
const unsigned CG_MAX_DXVERTEX_BUFFER_LEN = 32*1024;

// 默认支持的纹理数量,一千个左右，够了吧
const unsigned CG_DEFAULT_STORED_TEXTURE_NUM = 1024;

// 默认缓存的绘制单元个数：1000个左右
const unsigned CG_DEFAULT_RENDER_UNIT_CACHE_NUM = 1024;

// ------------------------------------------------------------------------------

// 绘制各种单元所需的顶点数
const unsigned CG_TEXTURE_NEED_VERTEX_NUM = 4;
const unsigned CG_RECT_NEED_VERTEX_NUM = 4;
const unsigned CG_LINE_NEED_VERTEX_NUM = 2;
const unsigned CG_BOX_NEED_VERTEX_NUM = 5;
const unsigned CG_POINT_NEED_VERTEX_NUM = 1;


// ------------------------------------------------------------------------------

// d3d绘制引擎的顶点格式定义
typedef struct tagD3DVertex
{
	float x, y, z, rhw;
	D3DCOLOR color;
	float u, v;
	static const DWORD FVF;
}cgD3DVertex;


// ------------------------------------------------------------------------------

// 绘制单元类型枚举，
// 由于暂时用的是缓存油画算法
// 所以要把所有的绘制单元缓存下来，然后按照顺序绘制
enum cgD3DRenderUnitType
{
	cgD3DRenderUnitType_None = 0,		// 无效
	cgD3DRenderUnitType_Primitive = 1,	// 图元：点线面，纹理三角形
	cgD3DRenderUnitType_Clear = 2,		// 清空背景
	cgD3DRenderUnitType_Surface = 3,	// 渲染表面
	cgD3DRenderUnitType_ViewPort = 4,	// 修改viewport
};

// 绘制单元
typedef struct tagD3DRenderUnit
{
	int _type;
	D3DPRIMITIVETYPE	_primitive;				// 图元类型
	UINT				_offset;				// 顶点偏移
	UINT				_count;				// 数量
	
	LPDIRECT3DTEXTURE9	_tex;			// 用到的贴图

	// 下面这个只为了清空而是用
	// _type == D3DPT_FORCE_DWORD
	LPDIRECT3DSURFACE9 _surface;	// 表面
	cgRectF _srcRect;
	cgRectF _destRect;


}cgD3DRenderUnit;

// ------------------------------------------------------------------------------

typedef cgStorage<cgD3DImage> cgD3DImageStorage;

// ------------------------------------------------------------------------------
// 字体列表
typedef std::vector<LPD3DXFONT> cgD3DFontPtrList;
// ------------------------------------------------------------------------------

struct cgRenderTargetMemo
{
	LPDIRECT3DSURFACE9 surface;
	D3DVIEWPORT9 viewPort;
};
// 渲染目标栈
typedef std::stack<cgRenderTargetMemo> cgD3DRenderTargetStack;
// ------------------------------------------------------------------------------
// 渲染目标相关

class cgDxRenderSurface:
	public cgRenderSurface
{
public:
	cgDxRenderSurface(LPDIRECT3DSURFACE9 lpSurface);
	virtual ~cgDxRenderSurface();

	virtual void* GetContent();
	virtual bool ReleaseContent(void * pContent);
	virtual int GetType();

	virtual LPDIRECT3DSURFACE9 GetD3DSurface();
private:
	LPDIRECT3DSURFACE9 m_lpSurface;
};


// ------------------------------------------------------------------------------

class cgD3DRenderImpl :
	public cgRenderImpl
{
public:
	cgD3DRenderImpl(void);
	virtual ~cgD3DRenderImpl(void);
public:
	// 初始化
	virtual bool Initialize(cgHwnd hWnd, int nWidth, int nHeight);

	// 重新设置大小
	virtual bool Resize(int nWidth, int nHeight);

	// 设置环境光
	virtual void SetAmbientLight(cgColor light);
	virtual cgColor GetAmbientLight();

	// 清空背景
	virtual void ClearBack(cgColor color);

	// 设置视口区
	virtual bool SetViewPort(const cgRectF& rect);
	bool DoSetViewPort(const cgRectF& rect);

	virtual void GetViewPort(cgRectF& rect);

	// 清空一个矩形
	virtual void ClearRect(const cgRectF& clearRect);
	void DoClearRect(const cgRectF & clearRect);

	// 开启绘制
	virtual void BeginRender();

	// 结束绘制
	virtual void EndRender();

	// 显示到屏幕
	virtual void Present();

	// 加载纹理
	virtual cgID LoadTexture(LPCTSTR lpctPath, int nOpertion = NULL);

	// 释放纹理
	virtual bool ReleaseTexture(cgID idTex);

	// 创建可以后台渲染的贴图
	virtual cgID CreateTexture(int nWidth, int nHeight);

	// 获取纹理大小
	virtual cgSize GetTextureSize(cgID idTex);

	//// 渲染纹理
	virtual void RenderTexture(cgID idTex, 
		const cgRectF& srcRect, 
		const cgRectF& destRect,
		cgColor color);

	// 绘制多边形
	virtual void RenderPolygon(const cgRenderVertex* pkVertexList, unsigned uVertexNum, cgID idTex);

	// 填充矩形
	virtual void FillRect(const cgRectF& destRect, cgColor color);

	// 绘制线框
	virtual void DrawBox(const cgRectF& destRect, cgColor color);

	// 绘制直线
	virtual void DrawLine(const cgPoint& fromPoint, const cgPoint& toPoint, 
		cgColor color);

	// 绘制点
	virtual void DrawPoint(const cgPoint& point, cgColor color);

	// 添加一种字体
	virtual cgID AddFont(const cgFontConfig& kConfig);

	// 绘制文字
	virtual void RenderTextDirectly(LPCTSTR lpctText, int nTextLen, 
		const cgRectF& destRect, unsigned uTextStyle = DT_CENTER|DT_VCENTER,
		cgColor color = 0xffffffff, unsigned uFontID = 0);

	// 获取字符串宽度
	virtual int CalcTextWidth(LPCTSTR lpctText, int nTextLen, cgID font, 
		int nMaxWidth = 0x0fffffff, int nMaxHeight = 0x0fffffff); 

	// 设置临时渲染目标
	virtual bool PushRenderTarget(cgID idTex);

	// 重置渲染目标
	virtual bool PopRenderTarget();

	// 立即显示所有绘制结果
	virtual void SetRenderDirty();

	// 截图
	virtual void ScreenShot(LPCTSTR lpctSavePath, cgScreenShotImageFormat enmFormat);

	// 开启反锯齿
	virtual void EnableTextureFilter(bool bEnable);

	// 创建一个可供渲染的表面
	cgRenderSurface * CreateRenderSurface(int w, int h, int nOpertion = 0);

	// 显示表面
	bool PresentRenderSurface(cgRenderSurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect);

public:

	// 获取d3d相关的设备
	LPDIRECT3DDEVICE9 GetDevice();

protected:
	
	// 设置渲染状态
	void SetupRenderState() ;

	// 设置贴图状态
	void SetupTextureStageState() ;

	bool PreOnLostDevice();
	bool OnLostDevice();
	bool OnResetDevice();
	// 创建顶点缓存
	bool CreateRenderBuffer();

	// 开始缓冲
	bool BeginCacheRenderUnits();

	// 停止缓冲，并把缓冲的绘制单元真正绘制到rendertarget
	bool EndCacheRenderUnits();

	// 检查顶点数据是否足够
	void EnsureVertexDataEnough(unsigned uNeedLen);

	// 根据id查找字体
	LPD3DXFONT FindFont(cgID id);

	// 渲染表面到屏幕
	bool DoPresentRenderSurface(LPDIRECT3DSURFACE9 lpSurface, const cgRectF& srcRect, const cgRectF& destRect);

protected:
	D3DPRESENT_PARAMETERS m_kPresentParams;
	LPDIRECT3D9 m_lpD3D;
	LPDIRECT3DDEVICE9 m_lpDevice;

	// 全局环境光
	cgColor m_uAmbientLight;

	// 顶点缓冲
	LPDIRECT3DVERTEXBUFFER9 m_lpVertexBuff;

	// 锁定后的缓冲
	cgD3DVertex * m_pkVertexData;

	// 已经使用的锁定后的缓冲
	unsigned m_uVertexDataOffset;

	// 所有的贴图的存储仓库
	cgD3DImageStorage * m_pkImageStorage;

	// 绘制列表
	cgD3DRenderUnit * m_pRenderUnitList;
	unsigned m_uRenderUnitNum;

	// 字体列表
	cgD3DFontPtrList m_kFontList;

	// rendertarget 保存的栈
	cgD3DRenderTargetStack m_kRenderTargetStack;
};

D3DXIMAGE_FILEFORMAT cgImageFormatToDxFormat(cgScreenShotImageFormat cgFormat);

#endif // cgDxRenderImp_h__

