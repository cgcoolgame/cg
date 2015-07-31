
// 提供与平台相关的封装

#ifndef cgPlatform_h__
#define cgPlatform_h__
#include "cgSingleton.h"

class cgRenderImpl;
class cgSoundPlayerImpl;
class cgWindow;

class cgPlatform
{
public:
	virtual ~cgPlatform(void);

	// 创建一个实际渲染器
	virtual cgRenderImpl * CreateRenderImpl() = NULL;

	// 创建一个声音播放器
	virtual cgSoundPlayerImpl * CreateSoundPlayerImpl() = NULL;

	// 创建一个渲染窗口
	virtual cgWindow * CreateAppWindow() = NULL;

public:
	// 这个是专用的，所以为了和一般的单件模式区别
	static cgPlatform * Instance();
	static void Destory();

protected:
	cgPlatform(void);

private:
	static cgPlatform * ms_pkPlatform;
};

#endif // cgPlatform_h__
