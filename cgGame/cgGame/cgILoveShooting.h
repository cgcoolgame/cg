////////////////////////////////////////////////
//	FileName:		cgILoveShooting.h
//	Author:			Master
//	Date:			2014.04.13 23:34
//	Description:	�Ұ���ɻ�
//	mark:			�������ڸ��ֶ���������һ����������Ϸ
////////////////////////////////////////////////
#ifndef cgILoveShooting_h__
#define cgILoveShooting_h__

#include "CGGameApp.h"
#include "cgSingleton.h"
#include "cgGameMessageListenerManager.h"


class cgILoveShooting :
	public cgGameApp,
	public cgSingleton<cgILoveShooting>,
	public cgGameMessageListener
{
public:
	cgILoveShooting(void);
	~cgILoveShooting(void);

	virtual bool OnGameMessage(cgGameMessage msg, void * pData, int nLen);
protected:
	virtual bool DoInitGame();
	virtual void DoUpdateGame(float fDeltaTime);
	virtual void DoRenderGame();
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);
};

#endif // cgILoveShooting_h__
