#ifndef cgGameCommandManager_h__
#define cgGameCommandManager_h__
#include "cgGameCommand.h"

// ���������
class cgGameCommandManager:
	public cgSingleton<cgGameCommandManager>
{
public:
	cgGameCommandManager();
	virtual ~cgGameCommandManager();

	// ��ʼ����ûƨ�ã�����Ϊ�˿���ͳһһЩ
	bool Initialize();

	// �������
	void AddGameCommand(cgGameCommandPtr spCommand);

	// ����
	bool Undo();

	// ����
	bool Redo();

private:
	cgGameCommandPtrList m_kUndoCommandList;
	cgGameCommandPtrList m_kRedoCommandList;
};

#endif // cgGameCommandManager_h__
