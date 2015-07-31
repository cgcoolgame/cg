#ifndef cgWindowsPlatform_h__
#define cgWindowsPlatform_h__
#include "cgPlatform.h"

class cgWindowsPlatform:
	public cgPlatform
{
public:
	friend class cgPlatform;

	// 创建一个实际渲染器
	virtual cgRenderImpl * CreateRenderImpl();

	// 创建一个声音播放器
	virtual cgSoundPlayerImpl * CreateSoundPlayerImpl();

	// 创建一个窗口
	virtual cgWindow * CreateAppWindow();

private:
	cgWindowsPlatform(void);
};

#endif // cgWindowsPlatform_h__
