#ifndef cgUIManager_h__
#define cgUIManager_h__
#include <list>

#include "cgUIWidget.h"
#include "cgUILoader.h"
#include "cgSingleton.h"


class cgUIEventListenerEx
{
public:
	// ����UI�¼�
	// ����ֵΪtrue��ʾ�Ե�����������������Ӧ��false��ʾ���Լ�����һ��
	virtual bool OnUIEvent(cgUIWidgetPtr spComponent, 
		cgUIEvent enmEvent, unsigned wparam, unsigned lparam) = NULL;
};

typedef std::list<cgUIEventListenerEx*> cgUIEventListenerList;

typedef std::list<cgRectF> cgDirtyRectList;

class cgUIRender;

class cgUIManager:
	public cgSingleton<cgUIManager>
{
public:
	cgUIManager();
	virtual ~cgUIManager(void);

public:
	// �ô��ھ���ͳߴ�����ʼ��
	virtual bool Initialize(cgHwnd hWnd, int nWidth, int nHeight);

	// ��Ϣ����
	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

	// ��Ⱦ,������ʾ�ǲ���ÿ֡����ʾ����Ļ
	// ��̬���棨������Ϸ���棩��Ҫÿ�ζ����Ƶ���Ļ��������true
	// ��̬��������Ҫÿ֡�����ƣ�ֻ��Ҫ��dirty��ʱ����Ƶ���Ļ����
	virtual void Render(bool bDisplayWhileNoDirty = true);

	// ����
	virtual void Update(float fTime);

//--------------------------------------------------------------------
	// �¼�����
	void OnUIEvent(cgUIWidgetPtr spComponent, 
		cgUIEvent enmEvent, unsigned wparam, unsigned lparam);

	// ���UI�¼�������
	void AddUIEventListener(cgUIEventListenerEx * pkListener);
	bool DelUIEventListener(cgUIEventListenerEx * pkListener);
//--------------------------------------------------------------------

	// ���Ժ���
	bool IsInEditMode();

	// ����Щ����Ӧ���У�UI������ʹ��ڿͻ����������ǲ�һ�µģ�Ҫ��һ�μ���
	// �󲿷�����£��������غϵ�ʱ���ǿ�ʵ��

	// �Ӵ��ڡ��ͻ���������ת��UI����
	void ClientPointToUI(int & x, int & y);

	// ��UI����ת�����ڡ��ͻ���������
	void UIPointToClient(int & x, int & y);

	// ��UI����ʾ����Ļ
	void UIPointToScreen(int & x, int & y);

	// ��������
	bool AddDirtyRect(const cgRectF& rect);
	unsigned GetDirtyRectNum();

	// �Ƿ���Ҫ�ػ�
	bool IsDirty();

	// ����Ϊ���»���
	void SetDirty();

	// ����ui������
	void SetUILoader(cgUILoader * pkLoader);

	// �л���һ����Ļ����Ļ��root����һ���Ŀؼ�����С��root��ȫһ����
	bool GotoScreen(const char * pcScreen);

	// ��õ�ǰ��Ļ
	cgUIWidgetPtr GetCurrentScreen();

	// ͨ��id������һ���ؼ����������̬���أ���ô���Ҳ�������ؼ���ʱ�򣬳��Զ�̬����
	// �ؼ�id�����ǿؼ���Ψһ��ʶ��һ���ʽ���£�root.game.MyFrame
	cgUIWidgetPtr FindComponent(const char * pcID, bool bLoadDynamic = false);

protected:

	// һЩ��ݼ�
	virtual bool ParseShortCut(unsigned wparam, unsigned lparam);

	// ����ͻ���������������ڵ�ƫ��
	void CalcClientToWinOff();
	void CalcUIToWinOff();

protected:
	// ������������
	cgHwnd m_hWnd;

	// �����ڳߴ�
	cgRectF m_kBound;

	// �ͻ�����ƫ��
	cgPoint m_kClientToWinOff;
	cgPoint m_kUIToWinOff;

	// UI������
	cgUILoader * m_pkUILoader;

	// ���е�UI�ĸ�
	cgUIWidgetPtr m_spRoot;	

	cgUIWidgetPtr m_spCurrentScreen;
	// ����
	cgUIWidgetPtr m_spFocusComponent;

	// hot
	cgUIWidgetPtr m_spMouseComponent;

	// ������б�
	cgDirtyRectList m_kDirtyRectList;

	// �¼�������
	cgUIEventListenerList	m_kUIEventListnerList;

	// �Ƿ��Ǳ༭ģʽ
	bool m_bInEditMode;

};

#endif // cgUIManager_h__
