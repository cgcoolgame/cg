//////////////////////////////////////////////////////////////////////////
//	FileName:		CGGameApp.h
//	Author:			Master
//	Date:			2014.4.15
//	Desc:			一个基于模板的游戏开发框架，用于快速游戏模型建立
//	Desc:			当然，这不是唯一的选择
//////////////////////////////////////////////////////////////////////////
#ifndef CGGameApp_h__
#define CGGameApp_h__

#include "cgWinApp.h"
#include "cgGameMessage.h"
#include "cgGameCommand.h"
#include "cgGameTask.h"
#include <list>

#define DEFAULT_GAME_MAX_FPS 60

class cgGameMessageListener;

class cgGameApp:
	public cgWinApp
{
public:
	cgGameApp();
	~cgGameApp(void);

public:
	// 初始化，并且创建一个指定大小的窗口
	virtual bool Initialize(int nWidth, int nHeight, 
		int nStyle = WS_OVERLAPPEDWINDOW, 
		int nStyleEx = WS_EX_APPWINDOW );

	// 消息处理函数
	virtual bool OnRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// 获取游戏App实例
	static cgGameApp * GetGameApp();
public:

	// 上一帧的开始时间
	float GetLastFrameBeginTime();

	// 当前帧的开始时间
	float GetFrameBeginTime();

	// 两帧之间的差值，也就是上一帧的持续时间
	float GetDeltaTime();

	// FPS相关
	void SetMaxFPS(int nFPS);
	int GetMaxFPS();
	int GetCurFPS();
	void ShowFPS(bool bShow);
	bool IsShowFPS();

	// 时间加速，可以控制加速、减速、甚至时间冻结
	void SetTimeScale(float fAccelerate);
	float GetTimeScale();

protected:

	virtual bool DoInitGame();
	// 实际处理消息
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// 窗口尺寸发生变化
	virtual bool OnSizeChanged();

	// 继承自cgApp，空闲时间片
	virtual void OnIdle();

	// 更新
	virtual void Update(float fDeltaTime);
	// 更新游戏逻辑
	virtual void DoUpdateGame(float fDeltaTime);

	// 渲染相关，清空、开启和显示
	void Render();
	// 具体渲染，子类继承，做一些额外绘制
	virtual void DoRenderGame();

	// FPS相关
	void LockFPS();
	void DrawFPS();

protected:

	// 上一帧的开始时间
	float m_fLastFrameBeginTime;

	// 当前帧的开始时间
	float m_fFrameBeginTime;

	// 当前帧和上一帧的时间差值
	float m_fFrameDeltaTime;

	// 时间加速比例
	float m_fTimeScale; // 时间倍数

	// 最大帧率
	int m_nMaxFPS;
	// 当前帧率
	int m_nCurFPS;
	// 是否显示帧率
	bool m_bShowFPS;
	
	// 是否加载完成
	bool m_bIsInitialized;
};

#endif // CGGameApp_h__
