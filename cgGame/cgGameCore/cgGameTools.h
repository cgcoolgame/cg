#ifndef cgGameTools_h__
#define cgGameTools_h__
#include "cgGameCommand.h"
#include "cgGameMessage.h"

// һЩ��Ϸ��ܵĹ��ߺ���

class cgGameTools
{
public:
	cgGameTools(void);
	~cgGameTools(void);

	// ����Ϸ��ܷ����������������ʱ����ʱС���㣬������ʧЧ
	static void PostGameCommand(cgGameCommandPtr spCommand, float fTimeDelay = -1.0f);

	// ����Ϸ��ܷ����Զ�����Ϣ���������ϴ���
	static bool PostGameMessage(cgGameMessage msg, void * pData = NULL, int nDataLen = 0);
};

#endif // cgGameTools_h__
