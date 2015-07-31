#ifndef cgGameCommand_h__
#define cgGameCommand_h__
#include <list>
#include "cgSingleton.h"
#include "cgRefObject.h"
#include "cgSmartPointer.h"

// 简单的游戏命令
// 命令和消息的区别：
//	>>命令可以延时执行，消息必须马上执行
//	>>命令只需要一个地方存储，消息必须要分发下去

class cgGameCommand:
	public cgRefObject
{
public:
	cgGameCommand(void);
	virtual ~cgGameCommand(void);

	// 执行命令
	virtual bool Execute(){return true;}

	// 撤销命令，暂时无用
	virtual bool Unexecute(){return true;}
};

// 智能指针
typedef cgSmartPointer<cgGameCommand> cgGameCommandPtr;

typedef std::list<cgGameCommandPtr> cgGameCommandPtrList;


#endif // cgGameCommand_h__
