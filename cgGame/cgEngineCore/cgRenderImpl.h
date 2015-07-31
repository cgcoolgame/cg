#ifndef cgRenderImpl_h__
#define cgRenderImpl_h__
#include "cgDefine.h"

class cgRenderSurface;

class cgRenderImpl
{
public:
	// ��������
	virtual ~cgRenderImpl(void){};

	// ��ʼ��
	virtual bool Initialize(cgHwnd hWnd, int nWidth, int nHeight) = NULL;

	// �������ô�С
	virtual bool Resize(int nWidth, int nHeight) = NULL;

	// ���������ӿ���
	virtual bool SetViewPort(const cgRectF& rect) = NULL;
	virtual void GetViewPort(cgRectF& rect) = NULL;

	// ��ձ���
	virtual void ClearBack(cgColor color) = NULL;

	// ���һ������
	virtual void ClearRect(const cgRectF& clearRect) = NULL;

	// ��������
	virtual void BeginRender() = NULL;

	// ��������
	virtual void EndRender() = NULL;

	// ��ʾ����Ļ
	virtual void Present() = NULL;
// -------------------------------------------------------------------------------------
	// ���û�����
	virtual void SetAmbientLight(cgColor light) = NULL;
	virtual cgColor GetAmbientLight() = NULL;

	// ����ţ�ƵĻ���ģʽ�������ã�
	virtual void EnableTextureFilter(bool bEnable) = NULL;
// -------------------------------------------------------------------------------------

	// ��������
	virtual cgID LoadTexture(LPCTSTR lpctPath, int nOpertion = NULL) = NULL;

	// �ͷ�����
	virtual bool ReleaseTexture(cgID idTex) = NULL;

	// �������Ժ�̨��Ⱦ����ͼ
	virtual cgID CreateTexture(int nWidth, int nHeight) = NULL;

	// ��ȡ�����С
	virtual cgSize GetTextureSize(cgID idTex) = NULL;

	// ��Ⱦ����
	virtual void RenderTexture(cgID idTex, 
		const cgRectF& srcRect, 
		const cgRectF& destRect,
		cgColor color) = NULL;
// -------------------------------------------------------------------------------------
	// ���ƶ����
	virtual void RenderPolygon(const cgRenderVertex* pkVertexList, unsigned uVertexNum,
		cgID idTex) = NULL;

	// ������
	virtual void FillRect(const cgRectF& destRect, cgColor color) = NULL;

	// �����߿�
	virtual void DrawBox(const cgRectF& destRect, cgColor color) = NULL;

	// ����ֱ��
	virtual void DrawLine(const cgPoint& fromPoint, const cgPoint& toPoint, 
		cgColor color) = NULL;

	// ���Ƶ�
	virtual void DrawPoint(const cgPoint& point, cgColor color) = NULL;
// -------------------------------------------------------------------------------------
	// ���һ������
	virtual cgID AddFont(const cgFontConfig& kConfig) = NULL;
	// ��������
	virtual void RenderTextDirectly(LPCTSTR lpctText, int nTextLen, 
		const cgRectF& destRect, unsigned uFontID = 0, 
		cgColor color = 0xffffffff,
		unsigned uTextStyle = DT_CENTER|DT_VCENTER) = NULL;

	// ��ȡ�ַ������
	virtual int CalcTextWidth(LPCTSTR lpctText, int nTextLen, cgID font, 
		int nMaxWidth = 0x0fffffff, int nMaxHeight = 0x0fffffff) = NULL; 
// -------------------------------------------------------------------------------------
	// ������ʱ��ȾĿ��
	virtual bool PushRenderTarget(cgID idTex) = NULL;

	// ������ȾĿ��
	virtual bool PopRenderTarget() = NULL;

	// ������ʾ���л��ƽ��
	virtual void SetRenderDirty() = NULL;

// -------------------------------------------------------------------------------------

	// ����һ���ɹ���Ⱦ�ı���
	virtual cgRenderSurface * CreateRenderSurface(int w, int h, int nOpertion = 0) = NULL;

	// ��ʾ����
	virtual	bool PresentRenderSurface(cgRenderSurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect) = NULL;
// -------------------------------------------------------------------------------------
	// ��ͼ
	virtual void ScreenShot(LPCTSTR lpctSavePath, cgScreenShotImageFormat enmFormat) = NULL;

};

#endif // cgRenderImpl_h__
