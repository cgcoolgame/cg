#ifndef cgWindowsPlatform_h__
#define cgWindowsPlatform_h__
#include "cgPlatform.h"

class cgWindowsPlatform:
	public cgPlatform
{
public:
	friend class cgPlatform;

	// ����һ��ʵ����Ⱦ��
	virtual cgRenderImpl * CreateRenderImpl();

	// ����һ������������
	virtual cgSoundPlayerImpl * CreateSoundPlayerImpl();

	// ����һ������
	virtual cgWindow * CreateAppWindow();

private:
	cgWindowsPlatform(void);
};

#endif // cgWindowsPlatform_h__
