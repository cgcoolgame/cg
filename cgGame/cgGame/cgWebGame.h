//////////////////////////////////////////////////////////////////////////
// һ���򵥵���å�������
// ��һ������ʽС�����ϼ�һ��web�ؼ����Ϳ�����һ���൱ʵ�õ���å�����ˡ�
// By Master
//////////////////////////////////////////////////////////////////////////

#ifndef cgWebGame_h__
#define cgWebGame_h__
#include "cgGdiplusApp.h"
#include <cgUILoader.h>
#include <cgUIManager.h>
#include <cgSingleton.h>

// ���ڳ���Ƚϼ򵥣�����UI��������UI��Ϣ��������������cgWebGame����
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
