#ifndef cgGameTools_h__
#define cgGameTools_h__
#include "cgGameCommand.h"
#include "cgGameMessage.h"

// 一些游戏框架的工具函数

class cgGameTools
{
public:
	cgGameTools(void);
	~cgGameTools(void);

	// 往游戏框架发送命令，可以设置延时，延时小于零，则立刻失效
	static void PostGameCommand(cgGameCommandPtr spCommand, float fTimeDelay = -1.0f);

	// 往游戏框架发送自定义消息，必须马上处理
	static bool PostGameMessage(cgGameMessage msg, void * pData = NULL, int nDataLen = 0);
};

#endif // cgGameTools_h__
