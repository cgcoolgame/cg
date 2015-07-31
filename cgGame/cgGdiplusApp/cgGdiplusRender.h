
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

	// ��ʼ��
	virtual bool Initialize(cgHwnd hWnd, int w, int h);

	// ���ü��о���
	virtual bool PushClipRect(const cgRectF& clipRect);
	virtual void PopClipRect();
	virtual void ClearRect(const cgRectF& rect);

	// ���ƿ���
	virtual void BeginRender();
	virtual void EndRender();
	virtual void Display();

	// ��������͸����
	virtual void SetAlpha(BYTE alpha);

	//����С�����仯
	virtual bool OnSizeChanged(int w, int h);
	// ����ͼƬ
	virtual cgID LoadImage(LPCTSTR path);
	virtual cgID LoadImage(cgID resID);
	virtual bool ReleaseImage(cgID image);

	virtual cgSize GetImageSize(cgID image);

	// ����
	virtual void DrawImage(cgID image, const cgRectF& srcRect, const cgRectF & destRect);

	virtual void DrawLine(const cgPoint& from, const cgPoint& to, cgColor color);

	virtual void DrawBox(const cgRectF& rect, cgColor color);

	virtual void FillRect(const cgRectF& rect, cgColor color);

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen,
		const cgRectF& rect, cgID font, int space , cgColor color, int style);

	virtual void DrawUIText(LPCTSTR lpctText, int nTextLen, 
		int x, int y, cgID font, cgColor color);

	// ����һ���ɹ���Ⱦ�ı���
	cgUISurface * CreateUISurface(int w, int h, int nOpertion = 0) ;

	// ��ʾ����
	bool PresentUISurface(cgUISurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect) ;

	// ��ȡ����ch�Ŀ��
	virtual int GetUICharWidth(TCHAR ch, cgID idFont) ;

	// ��ȡ����ch��size
	virtual cgSizeF GetUICharSize(TCHAR ch, cgID idFont);
public:

	static Gdiplus::Image * LoadImageFromResource(UINT nID, LPCTSTR sTR);
	static Gdiplus::Image * LoadImageFromFile(LPCTSTR lpctPath);
	static Gdiplus::Image * LoadImageFromMemory(void * pBuff, int nLen);

	static HBITMAP CreateDIBBitmap(int w, int h);

private:
	// ����Դ��ȡͼƬ��Ϣ

	// �ҵ�����
	Gdiplus::Font * FindFont(cgID font);

	// ��������
	bool LoadFonts();

	// ����һ��ͼƬ

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
