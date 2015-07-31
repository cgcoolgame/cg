//////////////////////////////////////////////////////////////////////////
// ����һ���������ڣ�ע�⣬�Ǵ������ڣ������Ӵ��ڣ�������ҳ��ȥ
// ������ƽ�д�����ʵ�֣�Ч����ã�������һ��ȱ�㣺
// ȱ�㣺��֧��͸���������Ƕ��㴰�ڣ������߼�UI�޷�����֮��
// ���ڲ�֧��͸�������������Ӵ��ڻ�����������ס�ˣ����Զ��������ǲ�Ҫ����Ӵ��ڵĺ�
// ����֮�⣬��������
//////////////////////////////////////////////////////////////////////////

#ifndef cgUIWebPageEx_h__
#define cgUIWebPageEx_h__

#include <atlbase.h>
#include <atlwin.h>
#include <exdisp.h>

#include "cgUIWidget.h"


class cgUIWebPageEx :
	public cgUIWidget
{
public:
	cgUIWebPageEx(void);
	~cgUIWebPageEx(void);

public:
	// ��ʼ��
	bool Initialize(cgHwnd hMainWnd, int x, int y, int w, int h);

	// ��������ؼ���webpage��ƫ�ƣ�Ĭ��web�ǳ��������ؼ���
	void SetWebpageOffset(int leftOffset, int rightOffset, int topOffset, int bottomOffset);

	// ������ĳ����ҳ
	bool Navigate(LPCTSTR url, bool bForceRefresh = false);
	const cgString& GetCurUrl();

	// ˢ����ҳ
	bool Refresh();

	// ���ڲ����߼�UI�����Ե�λ�úʹ�С�ı��ʱ����Ҫ
	//	����web�����λ�úʹ�С
	virtual void SetVisible(bool bVisible);

	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

protected:
	virtual void OnPositionChanged();
	virtual void OnSizeChanged();
private:

	// ������ҳ������Ӧ�µĴ�С��λ��
	void AdjustWebRect();

private:
	CAxWindow m_kContainer;
	IWebBrowser2 * m_pkBrower;

	cgString m_strUrl;
	int m_nLeftOffset;
	int m_nRightOffset;
	int m_nTopOffset;
	int m_nBottomOffset;
};

#endif // cgUIWebPageEx_h__
