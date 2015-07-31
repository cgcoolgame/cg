#ifndef cgGameCommandManager_h__
#define cgGameCommandManager_h__
#include "cgGameCommand.h"

// 命令管理器
class cgGameCommandManager:
	public cgSingleton<cgGameCommandManager>
{
public:
	cgGameCommandManager();
	virtual ~cgGameCommandManager();

	// 初始化，没屁用，就是为了看着统一一些
	bool Initialize();

	// 添加命令
	void AddGameCommand(cgGameCommandPtr spCommand);

	// 撤销
	bool Undo();

	// 重做
	bool Redo();

private:
	cgGameCommandPtrList m_kUndoCommandList;
	cgGameCommandPtrList m_kRedoCommandList;
};

#endif // cgGameCommandManager_h__
