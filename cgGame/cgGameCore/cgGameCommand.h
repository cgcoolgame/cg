#ifndef cgGameCommand_h__
#define cgGameCommand_h__
#include <list>
#include "cgSingleton.h"
#include "cgRefObject.h"
#include "cgSmartPointer.h"

// �򵥵���Ϸ����
// �������Ϣ������
//	>>���������ʱִ�У���Ϣ��������ִ��
//	>>����ֻ��Ҫһ���ط��洢����Ϣ����Ҫ�ַ���ȥ

class cgGameCommand:
	public cgRefObject
{
public:
	cgGameCommand(void);
	virtual ~cgGameCommand(void);

	// ִ������
	virtual bool Execute(){return true;}

	// ���������ʱ����
	virtual bool Unexecute(){return true;}
};

// ����ָ��
typedef cgSmartPointer<cgGameCommand> cgGameCommandPtr;

typedef std::list<cgGameCommandPtr> cgGameCommandPtrList;


#endif // cgGameCommand_h__
