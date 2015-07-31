
#ifndef cgUIRender_h__
#define cgUIRender_h__
#include "cgUIDef.h"

enum cgUIImageSurfaceType
{
	cgUIImageSurfaceTypeNone = 0,		// ��Ч��
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
	
	// ��ʼ��
	virtual bool Initialize(cgHwnd hWnd, int w, int h);

	// ���ü��о��Σ�push����Ĺ�ϵ��������pop֮ǰ����������ֻ��Խ��ԽС�����ܱ��
	virtual bool PushClipRect(const cgRectF& clipRect) = NULL;
	virtual void PopClipRect() = NULL;

	// ���һ�����Σ����Ϊ��ȫ͸��
	virtual void ClearRect(const cgRectF& rect) = NULL;

	// ��ʼ����
	virtual void BeginRender() = NULL;
	virtual void EndRender() = NULL;
	virtual void Display() = NULL;

	//����С�����仯
	virtual bool OnSizeChanged(int w, int h) = 0;
	// ����ͼƬ
	virtual cgID LoadImage(LPCTSTR path)= NULL;
	virtual cgID LoadImage(cgID resID)= NULL;
	virtual bool ReleaseImage(cgID image) = NULL;

	// ��ȡͼƬ�ĳߴ�
	virtual cgSize GetImageSize(cgID image) = NULL;

	// ����
	virtual void DrawImage(cgID image, const cgRectF& srcRect, const cgRectF & destRect) = NULL;

	virtual void DrawLine(const cgPoint& from, const cgPoint& to, cgColor color) = NULL;

	virtual void DrawBox(const cgRectF& rect, cgColor color) = NULL;

	virtual void FillRect(const cgRectF& rect, cgColor color) = NULL;

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen,
		const cgRectF& rect, cgID font, int space , cgColor color, int style) = NULL;

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen, 
		int x, int y, cgID font, cgColor color) = NULL;

	// ����һ���ɹ���Ⱦ�ı���
	virtual cgUISurface * CreateUISurface(int w, int h, int nOpertion = 0) = NULL;

	// ��ʾ����
	virtual bool PresentUISurface(cgUISurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect) = NULL;

	// ��ȡ����ch�Ŀ��
	virtual int GetUICharWidth(TCHAR ch, cgID idFont) = NULL;

	// ��ȡ����ch��size
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
