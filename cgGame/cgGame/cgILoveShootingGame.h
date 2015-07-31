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
	// 初始化
	bool Initialize(cgHwnd hWnd, int w, int h);

	// 消息处理
	bool OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// 更新
	void Update(float fDeltaTime);

	// 渲染
	void Render();

	// 开始游戏
	bool Start();

	int GetWidth();
	int GetHeight();

	// 游戏内部消息
	virtual bool OnGameMessage(cgGameMessage msg, void * pData, int nLen);
public:

	// 加载UI，先手动写，成熟用法应该是通过读配置的
	virtual bool LoadAllUIs(cgUIWidgetPtr spRoot, int w, int h, cgHwnd hWnd);
	virtual cgUIWidgetPtr LoadScreen(const char * pcScreen);	
	//virtual cgUIComponentPtr Loadu
	virtual cgUIWidgetPtr LoadDynamic(const char * pcID) {return NULL;}


	// UI事件处理
	virtual bool OnUIEvent(cgUIWidgetPtr spComponent, 
		cgUIEvent enmEvent, unsigned wparam, unsigned lparam);

	void InitMainCraft();
	cgAircraftPtr GetMainCraft();
protected:
	// 消息处理
	bool OnClick(cgUIWidgetPtr spComponent, unsigned wparam, unsigned lparam);
	bool OnMouseIn(cgUIWidgetPtr spComponent, unsigned wparam, unsigned lparam);
protected:
	// 下面是界面切换逻辑，用C++实现脚本的功能，果然很蛋疼
	// ---------------------------------------------------------------------
	bool GotoDlgPanel();	// 切换到对话面板
	bool ShowDlg();			// 刷新对话
	// ---------------------------------------------------------------------
	bool GotoSelPanel();	// 切换到战机选择屏幕
	// ---------------------------------------------------------------------------------------------------------
	bool GotoGamePanel();	// 切换到游戏屏幕

private:
	int m_nWidth;
	int m_nHeight;
	cgAircraftPtr m_spMainCraft;

	int m_nKillNum;
	int m_nBeKilledNum;
	cgID m_idBgm;
};

#endif // cgILoveShootingGame_h__
