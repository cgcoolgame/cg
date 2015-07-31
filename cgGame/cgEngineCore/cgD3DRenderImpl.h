////////////////////////////////////////////////
//	FileName:		cgDxRenderImp.h
//	Author:			Master
//	Date:			2014.03.8
//	Description:	d3d ��render����һ�η�װ����N�Σ������Բ������һ��
//	mark:			ÿ�����һ���
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

// Ԥ����Ķ��������:1000���������ң�������
const unsigned CG_MAX_DXVERTEX_BUFFER_LEN = 32*1024;

// Ĭ��֧�ֵ���������,һǧ�����ң����˰�
const unsigned CG_DEFAULT_STORED_TEXTURE_NUM = 1024;

// Ĭ�ϻ���Ļ��Ƶ�Ԫ������1000������
const unsigned CG_DEFAULT_RENDER_UNIT_CACHE_NUM = 1024;

// ------------------------------------------------------------------------------

// ���Ƹ��ֵ�Ԫ����Ķ�����
const unsigned CG_TEXTURE_NEED_VERTEX_NUM = 4;
const unsigned CG_RECT_NEED_VERTEX_NUM = 4;
const unsigned CG_LINE_NEED_VERTEX_NUM = 2;
const unsigned CG_BOX_NEED_VERTEX_NUM = 5;
const unsigned CG_POINT_NEED_VERTEX_NUM = 1;


// ------------------------------------------------------------------------------

// d3d��������Ķ����ʽ����
typedef struct tagD3DVertex
{
	float x, y, z, rhw;
	D3DCOLOR color;
	float u, v;
	static const DWORD FVF;
}cgD3DVertex;


// ------------------------------------------------------------------------------

// ���Ƶ�Ԫ����ö�٣�
// ������ʱ�õ��ǻ����ͻ��㷨
// ����Ҫ�����еĻ��Ƶ�Ԫ����������Ȼ����˳�����
enum cgD3DRenderUnitType
{
	cgD3DRenderUnitType_None = 0,		// ��Ч
	cgD3DRenderUnitType_Primitive = 1,	// ͼԪ�������棬����������
	cgD3DRenderUnitType_Clear = 2,		// ��ձ���
	cgD3DRenderUnitType_Surface = 3,	// ��Ⱦ����
	cgD3DRenderUnitType_ViewPort = 4,	// �޸�viewport
};

// ���Ƶ�Ԫ
typedef struct tagD3DRenderUnit
{
	int _type;
	D3DPRIMITIVETYPE	_primitive;				// ͼԪ����
	UINT				_offset;				// ����ƫ��
	UINT				_count;				// ����
	
	LPDIRECT3DTEXTURE9	_tex;			// �õ�����ͼ

	// �������ֻΪ����ն�����
	// _type == D3DPT_FORCE_DWORD
	LPDIRECT3DSURFACE9 _surface;	// ����
	cgRectF _srcRect;
	cgRectF _destRect;


}cgD3DRenderUnit;

// ------------------------------------------------------------------------------

typedef cgStorage<cgD3DImage> cgD3DImageStorage;

// ------------------------------------------------------------------------------
// �����б�
typedef std::vector<LPD3DXFONT> cgD3DFontPtrList;
// ------------------------------------------------------------------------------

struct cgRenderTargetMemo
{
	LPDIRECT3DSURFACE9 surface;
	D3DVIEWPORT9 viewPort;
};
// ��ȾĿ��ջ
typedef std::stack<cgRenderTargetMemo> cgD3DRenderTargetStack;
// ------------------------------------------------------------------------------
// ��ȾĿ�����

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
	// ��ʼ��
	virtual bool Initialize(cgHwnd hWnd, int nWidth, int nHeight);

	// �������ô�С
	virtual bool Resize(int nWidth, int nHeight);

	// ���û�����
	virtual void SetAmbientLight(cgColor light);
	virtual cgColor GetAmbientLight();

	// ��ձ���
	virtual void ClearBack(cgColor color);

	// �����ӿ���
	virtual bool SetViewPort(const cgRectF& rect);
	bool DoSetViewPort(const cgRectF& rect);

	virtual void GetViewPort(cgRectF& rect);

	// ���һ������
	virtual void ClearRect(const cgRectF& clearRect);
	void DoClearRect(const cgRectF & clearRect);

	// ��������
	virtual void BeginRender();

	// ��������
	virtual void EndRender();

	// ��ʾ����Ļ
	virtual void Present();

	// ��������
	virtual cgID LoadTexture(LPCTSTR lpctPath, int nOpertion = NULL);

	// �ͷ�����
	virtual bool ReleaseTexture(cgID idTex);

	// �������Ժ�̨��Ⱦ����ͼ
	virtual cgID CreateTexture(int nWidth, int nHeight);

	// ��ȡ�����С
	virtual cgSize GetTextureSize(cgID idTex);

	//// ��Ⱦ����
	virtual void RenderTexture(cgID idTex, 
		const cgRectF& srcRect, 
		const cgRectF& destRect,
		cgColor color);

	// ���ƶ����
	virtual void RenderPolygon(const cgRenderVertex* pkVertexList, unsigned uVertexNum, cgID idTex);

	// ������
	virtual void FillRect(const cgRectF& destRect, cgColor color);

	// �����߿�
	virtual void DrawBox(const cgRectF& destRect, cgColor color);

	// ����ֱ��
	virtual void DrawLine(const cgPoint& fromPoint, const cgPoint& toPoint, 
		cgColor color);

	// ���Ƶ�
	virtual void DrawPoint(const cgPoint& point, cgColor color);

	// ���һ������
	virtual cgID AddFont(const cgFontConfig& kConfig);

	// ��������
	virtual void RenderTextDirectly(LPCTSTR lpctText, int nTextLen, 
		const cgRectF& destRect, unsigned uTextStyle = DT_CENTER|DT_VCENTER,
		cgColor color = 0xffffffff, unsigned uFontID = 0);

	// ��ȡ�ַ������
	virtual int CalcTextWidth(LPCTSTR lpctText, int nTextLen, cgID font, 
		int nMaxWidth = 0x0fffffff, int nMaxHeight = 0x0fffffff); 

	// ������ʱ��ȾĿ��
	virtual bool PushRenderTarget(cgID idTex);

	// ������ȾĿ��
	virtual bool PopRenderTarget();

	// ������ʾ���л��ƽ��
	virtual void SetRenderDirty();

	// ��ͼ
	virtual void ScreenShot(LPCTSTR lpctSavePath, cgScreenShotImageFormat enmFormat);

	// ���������
	virtual void EnableTextureFilter(bool bEnable);

	// ����һ���ɹ���Ⱦ�ı���
	cgRenderSurface * CreateRenderSurface(int w, int h, int nOpertion = 0);

	// ��ʾ����
	bool PresentRenderSurface(cgRenderSurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect);

public:

	// ��ȡd3d��ص��豸
	LPDIRECT3DDEVICE9 GetDevice();

protected:
	
	// ������Ⱦ״̬
	void SetupRenderState() ;

	// ������ͼ״̬
	void SetupTextureStageState() ;

	bool PreOnLostDevice();
	bool OnLostDevice();
	bool OnResetDevice();
	// �������㻺��
	bool CreateRenderBuffer();

	// ��ʼ����
	bool BeginCacheRenderUnits();

	// ֹͣ���壬���ѻ���Ļ��Ƶ�Ԫ�������Ƶ�rendertarget
	bool EndCacheRenderUnits();

	// ��鶥�������Ƿ��㹻
	void EnsureVertexDataEnough(unsigned uNeedLen);

	// ����id��������
	LPD3DXFONT FindFont(cgID id);

	// ��Ⱦ���浽��Ļ
	bool DoPresentRenderSurface(LPDIRECT3DSURFACE9 lpSurface, const cgRectF& srcRect, const cgRectF& destRect);

protected:
	D3DPRESENT_PARAMETERS m_kPresentParams;
	LPDIRECT3D9 m_lpD3D;
	LPDIRECT3DDEVICE9 m_lpDevice;

	// ȫ�ֻ�����
	cgColor m_uAmbientLight;

	// ���㻺��
	LPDIRECT3DVERTEXBUFFER9 m_lpVertexBuff;

	// ������Ļ���
	cgD3DVertex * m_pkVertexData;

	// �Ѿ�ʹ�õ�������Ļ���
	unsigned m_uVertexDataOffset;

	// ���е���ͼ�Ĵ洢�ֿ�
	cgD3DImageStorage * m_pkImageStorage;

	// �����б�
	cgD3DRenderUnit * m_pRenderUnitList;
	unsigned m_uRenderUnitNum;

	// �����б�
	cgD3DFontPtrList m_kFontList;

	// rendertarget �����ջ
	cgD3DRenderTargetStack m_kRenderTargetStack;
};

D3DXIMAGE_FILEFORMAT cgImageFormatToDxFormat(cgScreenShotImageFormat cgFormat);

#endif // cgDxRenderImp_h__

