#ifndef cgILoveShootingGame_h__
#define cgILoveShootingGame_h__
#include "cgSingleton.h"
#include "cgUIManager.h"
#include "cgImage.h"
#include "cgGameMessageListenerManager.h"
#include "cgILoveShootingDef.h"

class cgAircraft;

class cgILoveShootingGame:
	public cgSingleton<cgILoveShootingGame>,
	public cgUILoader,
	public cgUIEventListenerEx,
	public cgGameMessageListener
{
public:
	cgILoveShootingGame(void);
	~cgILoveShootingGame(void);

public:
	// ��ʼ��
	bool Initialize(cgHwnd hWnd, int w, int h);

	// ��Ϣ����
	bool OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// ����
	void Update(float fDeltaTime);

	// ��Ⱦ
	void Render();

	// ��ʼ��Ϸ
	bool Start();

	int GetWidth();
	int GetHeight();

	// ��Ϸ�ڲ���Ϣ
	virtual bool OnGameMessage(cgGameMessage msg, void * pData, int nLen);
public:

	// ����UI�����ֶ�д�������÷�Ӧ����ͨ�������õ�
	virtual bool LoadAllUIs(cgUIWidgetPtr spRoot, int w, int h, cgHwnd hWnd);
	virtual cgUIWidgetPtr LoadScreen(const char * pcScreen);	
	//virtual cgUIComponentPtr Loadu
	virtual cgUIWidgetPtr LoadDynamic(const char * pcID) {return NULL;}


	// UI�¼�����
	virtual bool OnUIEvent(cgUIWidgetPtr spComponent, 
		cgUIEvent enmEvent, unsigned wparam, unsigned lparam);

	void InitMainCraft();
	cgAircraftPtr GetMainCraft();
protected:
	// ��Ϣ����
	bool OnClick(cgUIWidgetPtr spComponent, unsigned wparam, unsigned lparam);
	bool OnMouseIn(cgUIWidgetPtr spComponent, unsigned wparam, unsigned lparam);
protected:
	// �����ǽ����л��߼�����C++ʵ�ֽű��Ĺ��ܣ���Ȼ�ܵ���
	// ---------------------------------------------------------------------
	bool GotoDlgPanel();	// �л����Ի����
	bool ShowDlg();			// ˢ�¶Ի�
	// ---------------------------------------------------------------------
	bool GotoSelPanel();	// �л���ս��ѡ����Ļ
	// ---------------------------------------------------------------------------------------------------------
	bool GotoGamePanel();	// �л�����Ϸ��Ļ

private:
	int m_nWidth;
	int m_nHeight;
	cgAircraftPtr m_spMainCraft;

	int m_nKillNum;
	int m_nBeKilledNum;
	cgID m_idBgm;
};

#endif // cgILoveShootingGame_h__
