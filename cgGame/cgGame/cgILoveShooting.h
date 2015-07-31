////////////////////////////////////////////////
//	FileName:		cgILoveShooting.h
//	Author:			Master
//	Date:			2014.04.13 23:34
//	Description:	我爱打飞机
//	mark:			利用现在各种东西，制作一个完整的游戏
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
