#ifndef cgUIManager_h__
#define cgUIManager_h__
#include <list>

#include "cgUIWidget.h"
#include "cgUILoader.h"
#include "cgSingleton.h"


class cgUIEventListenerEx
{
public:
	// 监听UI事件
	// 返回值为true表示吃掉，不允许其他人响应，false表示可以继续下一个
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
	// 用窗口句柄和尺寸来初始化
	virtual bool Initialize(cgHwnd hWnd, int nWidth, int nHeight);

	// 消息处理
	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

	// 渲染,参数表示是不是每帧都显示到屏幕
	// 动态界面（比如游戏界面）需要每次都绘制到屏幕，所以是true
	// 静态界面则不需要每帧都绘制，只需要在dirty的时候绘制到屏幕即可
	virtual void Render(bool bDisplayWhileNoDirty = true);

	// 更新
	virtual void Update(float fTime);

//--------------------------------------------------------------------
	// 事件处理
	void OnUIEvent(cgUIWidgetPtr spComponent, 
		cgUIEvent enmEvent, unsigned wparam, unsigned lparam);

	// 添加UI事件监听器
	void AddUIEventListener(cgUIEventListenerEx * pkListener);
	bool DelUIEventListener(cgUIEventListenerEx * pkListener);
//--------------------------------------------------------------------

	// 调试函数
	bool IsInEditMode();

	// 在有些具体应用中，UI的坐标和窗口客户区的坐标是不一致的，要做一次兼容
	// 大部分情况下，即两者重合的时候，是空实现

	// 从窗口“客户区”坐标转到UI坐标
	void ClientPointToUI(int & x, int & y);

	// 从UI坐标转到窗口“客户区”坐标
	void UIPointToClient(int & x, int & y);

	// 从UI到显示器屏幕
	void UIPointToScreen(int & x, int & y);

	// 添加脏矩形
	bool AddDirtyRect(const cgRectF& rect);
	unsigned GetDirtyRectNum();

	// 是否需要重绘
	bool IsDirty();

	// 设置为重新绘制
	void SetDirty();

	// 设置ui加载器
	void SetUILoader(cgUILoader * pkLoader);

	// 切换到一个屏幕，屏幕是root下面一级的控件，大小和root完全一样。
	bool GotoScreen(const char * pcScreen);

	// 获得当前屏幕
	cgUIWidgetPtr GetCurrentScreen();

	// 通过id来查找一个控件，如果允许动态加载，那么在找不到这个控件的时候，尝试动态加载
	// 控件id：就是控件的唯一标识，一般格式如下：root.game.MyFrame
	cgUIWidgetPtr FindComponent(const char * pcID, bool bLoadDynamic = false);

protected:

	// 一些快捷键
	virtual bool ParseShortCut(unsigned wparam, unsigned lparam);

	// 计算客户端相对于整个窗口的偏移
	void CalcClientToWinOff();
	void CalcUIToWinOff();

protected:
	// 关联的主窗体
	cgHwnd m_hWnd;

	// 主窗口尺寸
	cgRectF m_kBound;

	// 客户端区偏移
	cgPoint m_kClientToWinOff;
	cgPoint m_kUIToWinOff;

	// UI加载器
	cgUILoader * m_pkUILoader;

	// 所有的UI的根
	cgUIWidgetPtr m_spRoot;	

	cgUIWidgetPtr m_spCurrentScreen;
	// 焦点
	cgUIWidgetPtr m_spFocusComponent;

	// hot
	cgUIWidgetPtr m_spMouseComponent;

	// 脏矩形列表
	cgDirtyRectList m_kDirtyRectList;

	// 事件接受者
	cgUIEventListenerList	m_kUIEventListnerList;

	// 是否是编辑模式
	bool m_bInEditMode;

};

#endif // cgUIManager_h__
