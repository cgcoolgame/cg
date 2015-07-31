
// �ṩ��ƽ̨��صķ�װ

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

	// ����һ��ʵ����Ⱦ��
	virtual cgRenderImpl * CreateRenderImpl() = NULL;

	// ����һ������������
	virtual cgSoundPlayerImpl * CreateSoundPlayerImpl() = NULL;

	// ����һ����Ⱦ����
	virtual cgWindow * CreateAppWindow() = NULL;

public:
	// �����ר�õģ�����Ϊ�˺�һ��ĵ���ģʽ����
	static cgPlatform * Instance();
	static void Destory();

protected:
	cgPlatform(void);

private:
	static cgPlatform * ms_pkPlatform;
};

#endif // cgPlatform_h__
