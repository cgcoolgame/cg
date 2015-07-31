#ifndef cgUIWebPage_h__
#define cgUIWebPage_h__

// ����һ����ҳ��ʾ������ʱֻ֧��windows api���Ժ���ܻ���չ��
// ͨ������һ�������ڵ��Ӵ�����ʵ����ʾ��ҳ�ģ������ϸ������ϵ��߼�UI

// ע�⣺�����ͨ��������������ʾ����Ļ�ģ�����Ч�ʿ����Բ
// ȱ�㻹�о��ǳ��˵�����ӣ������Ĳ������ܳٶۡ�������������
// ��꿴������˸���ȵȸ���ȱ��
// �������ġ��߼�UI��������ã��������ڿ��Ը�������
// ������ʾ����������ر���Ҫ������ʹ��cgUIWebPageEx�������ҳ��ʾ��

#include "cgUIWidget.h"
#include <atlbase.h>
#include <atlwin.h>
#include <exdisp.h>

class cgUISurface;

class cgUIWebPage :
	public cgUIWidget
{
public:
	cgUIWebPage(void);
	~cgUIWebPage(void);

public:
	// ��ʼ��
	bool Initialize(cgHwnd hMainWnd, int x, int y, int w, int h);

	// ������ĳ����ҳ
	bool Navigate(LPCTSTR url, bool bForceRefresh = false);

	bool Refresh();

	// ���ڲ����߼�UI�����Ե�λ�úʹ�С�ı��ʱ����Ҫ
	//	����web�����λ�úʹ�С
	virtual void SetSize(int w, int h);
	virtual void Move(int x, int y);

	// �����������µ�ʱ����
	void SetFreshTimeSpace(float fTimeSpace);
	float GetFreshTimeSpace();

protected:

	// ����
	virtual void Update(float fTime);

	// ����
	virtual void DrawBackPic(const cgRectF& clipRect);

private:

	// ������ҳ������Ӧ�µĴ�С��λ��
	void AdjustWebRect();

private:
	CAxWindow m_kContainer;
	IWebBrowser2 * m_pkBrower;

	float m_fLastUpdateTime;
	float m_fFreshTimeSpace;// �������µ�ʱ����

	cgUISurface * m_pkRenderSurface;
};

#endif // cgUIWebPage_h__
