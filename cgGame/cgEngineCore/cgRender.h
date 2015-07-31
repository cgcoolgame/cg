
#ifndef I2DRender_h__
#define I2DRender_h__
#include "cgSingleton.h"

/************************************************************************/
/* �������µ�render�ṹ�������������ڣ���N���ˣ�ÿ�ζ������ջ�          */
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
	// ��ʼ��
	bool Initialize(cgHwnd hWnd, int nWidth, int nHeight);

	// �������ô�С
	bool Resize(int nWidth, int nHeight);

	// ���������ӿ���
	virtual bool SetViewPort(const cgRectF& rect);
	virtual void GetViewPort(cgRectF& rect);

	// ��ձ���
	void ClearBack(cgColor color);

	// ���һ������
	void ClearRect(const cgRectF& clearRect);

	// ��Ⱦ����
	void BeginRender();
	void EndRender();

	// ��ʾ����Ļ
	void Present();

// -------------------------------------------------------------------------------------

	// ���û�����
	void SetAmbientLight(cgColor light);
	cgColor GetAmbientLight();
// -------------------------------------------------------------------------------------
	// ����һ��ͼƬ
	cgID LoadTexture(LPCTSTR lpctImagePath, int nOption = NULL);

	// �ͷ�һ��ͼƬ
	bool ReleaseTexture(cgID id);

	// �������Ժ�̨��Ⱦ����ͼ
	cgID CreateTexture(int nWidth, int nHeight);

	// ��ȡͼƬ�ߴ�
	cgSize GetTextureSize(cgID id);

// -------------------------------------------------------------------------------------
	void RenderTexture(cgID id, const cgRectF& srcRect, 
		const cgRectF& destRect,
		cgColor color);
	// ͼԪ����
	void FillRect(const cgRectF& destRect, cgColor color);

	// �����߿�
	void DrawBox(const cgRectF& destRect, cgColor color);

	// ����ֱ��
	void RenderLine(const cgPoint& fromPoint, const cgPoint& toPoint, 
		cgColor color);

	// ���Ƶ�
	void RenderPoint(const cgPoint& point, cgColor color);

	// ���ƶ���Σ��Ƚ�ͨ�õĺ���
	void RenderPolygon(const cgRenderVertex* pkVertexList, unsigned uVertexNum,
		cgID idTexImage = CG_INVALID_ID);
// -------------------------------------------------------------------------------------
	// ��ȡ����ch�Ŀ��
	int GetRenderCharWidth(TCHAR ch, cgID idFont);

	// ��ȡ����ch�Ŀ��
	cgSizeF GetRenderCharSize(TCHAR ch, cgID idFont);

	// �����ַ���
	bool MeasureString(LPCTSTR text, int len, cgID font, 
		float & w, float & h, 
		float space, float scale);

	// ��������,�ҲŲ�������ô�Ű���
	// �����Ҵ����￪ʼ���ƣ��Ҿʹ�������ƣ�����������
	void RenderString(LPCTSTR lpctText, int nTextLen, 
		float x, float y, cgID font, cgColor color);

	// �ðɣ����ջ�����Ļ���render����Ҫ���Ű��
	void RenderString(LPCTSTR lpctText, int nTextLen,
		const cgRectF& rect, cgID font, float space , 
		cgColor color, unsigned style, float scale = 1.0f);
	
// -------------------------------------------------------------------------------------

	// ������ʱ��ȾĿ��
	bool PushRenderTarget(cgID id);

	// ������ȾĿ��
	bool PopRenderTarget();

	// ������ʾ���л��ƽ��
	void SetRenderDirty();

// -------------------------------------------------------------------------------------

	// ����һ���ɹ���Ⱦ�ı���
	cgRenderSurface * CreateRenderSurface(int w, int h, int nOpertion = 0) ;

	// ��ʾ����
	bool PresentRenderSurface(cgRenderSurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect);

// -------------------------------------------------------------------------------------

	// ��ͼ
	void ScreenShot(LPCTSTR lpctSavePath, cgScreenShotImageFormat enmFormat);

// -------------------------------------------------------------------------------------
protected:
	cgRenderImpl	* m_pkRenderImpl;
};

#endif // I2DRender_h__
