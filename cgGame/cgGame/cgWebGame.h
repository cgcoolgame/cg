//////////////////////////////////////////////////////////////////////////
// 一个简单的流氓弹窗软件
// 在一个弹出式小窗口上加一个web控件，就可以做一个相当实用的流氓弹窗了。
// By Master
//////////////////////////////////////////////////////////////////////////

#ifndef cgWebGame_h__
#define cgWebGame_h__
#include "cgGdiplusApp.h"
#include <cgUILoader.h>
#include <cgUIManager.h>
#include <cgSingleton.h>

// 由于程序比较简单，所以UI创建器和UI消息处理器都绑定在了cgWebGame上了
class cgWebGame:
	public cgGdiplusApp,
	public cgUILoader,
	public cgUIEventListenerEx,
	public cgSingleton<cgWebGame>
{
public:
	cgWebGame(void);
	~cgWebGame(void);

public:
	virtual cgUIWidgetPtr LoadScreen(const char * pcScreen);
	virtual cgUIWidgetPtr LoadDynamic(const char * pcID);

	virtual bool OnUIEvent(cgUIWidgetPtr spComponent, 
		cgUIEvent enmEvent, unsigned wparam, unsigned lparam);

protected:
	virtual bool DoInitialize();

};

#endif // cgWebGame_h__
