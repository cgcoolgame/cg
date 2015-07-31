
#ifndef cgGameUIRender_h__
#define cgGameUIRender_h__
#include "cgUIRender.h"
#include "cgSingleton.h"
#include "cgStorage.h"
#include "cgRender.h"
#include "cgImage.h"
#include <stack>

typedef cgStorage<cgImage> cgImageStorage;

class cgGameUISurface:
	public cgUISurface
{
public:
	cgGameUISurface(cgRenderSurface * pkSurface);
	virtual ~cgGameUISurface();

	virtual void * GetContent();
	virtual bool ReleaseContent(void * pContent);
	virtual int GetType();

	cgRenderSurface * GetRenderSurface();
private:
	cgRenderSurface * m_pkSurface;
};

class cgGameUIRender :
	public cgUIRender, public cgSingleton<cgGameUIRender>
{
public:
	cgGameUIRender(void);
	virtual ~cgGameUIRender(void);
public:
	// ��ʼ��
	virtual bool Initialize(cgHwnd hWnd, int w, int h);

	// ���ü���
	virtual bool PushClipRect(const cgRectF& clipRect);
	virtual void PopClipRect();
	virtual void ClearRect(const cgRectF& rect);

	// ���ƿ���
	virtual void BeginRender();
	virtual void EndRender();
	virtual void Display() ;

	//����С�����仯
	virtual bool OnSizeChanged(int w, int h);
	// ����ͼƬ
	virtual cgID LoadImage(LPCTSTR path);
	virtual cgID LoadImage(cgID resID);
	virtual bool ReleaseImage(cgID image);

	virtual cgSize GetImageSize(cgID image) ;

	// ����
	virtual void DrawImage(cgID image, const cgRectF& srcRect, const cgRectF & destRect) ;

	virtual void DrawLine(const cgPoint& from, const cgPoint& to, cgColor color) ;

	virtual void DrawBox(const cgRectF& rect, cgColor color);

	virtual void FillRect(const cgRectF& rect, cgColor color);

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen,
		const cgRectF& rect, cgID font, int space , cgColor color, int style);

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen, 
		int x, int y, cgID font, cgColor color) ;

	// ����һ���ɹ���Ⱦ�ı���
	cgUISurface * CreateUISurface(int w, int h, int nOpertion = 0) ;

	// ��ʾ����
	bool PresentUISurface(cgUISurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect) ;

	// ��ȡ����ch�Ŀ��
	virtual int GetUICharWidth(TCHAR ch, cgID idFont);

	// ��ȡ����ch��size
	virtual cgSizeF GetUICharSize(TCHAR ch, cgID idFont);
private:
	cgImagePtr m_spBkImage;	// ����һ����̨����
	cgImageStorage *m_pkImageStorage;

	cgRectF m_kCurClipRect;
	typedef std::stack<cgRectF> ClipRectStack;
	ClipRectStack m_kClipRectStack;
};

#endif // cgGameUIRender_h__
