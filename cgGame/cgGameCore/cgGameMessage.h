#ifndef cgGameMessage_h__
#define cgGameMessage_h__


// ��Ϸ�ڲ���Ϣ����OnMessage��OnWinMessage����Ϣ��һ��
// ר����OnGameMessage����Ϸ�ڲ���Ϣ��ϵͳ��Ϣ����ʱ���ֿ�����

typedef int cgGameMessage;

// -------------------------------------------------------------------------------

//	���ﶨ������Ϣ
static const cgGameMessage cgGameMessage_GameAppInitialized = 1;
static const cgGameMessage cgGameMessage_LogoStarted = 2;
static const cgGameMessage cgGameMessage_LogoFinished = 3;

// -------------------------------------------------------------------------------

// ��������Ϸʹ�õ���Ϣ��10000��ʼ��
// С�����ֵ����Ϣֻ�ܿ����ʹ��
// Ϊ�˷�ֹid��ͻ���벻Ҫ����
static const cgGameMessage cgUserGameMessageBegin = 10000;	


// -------------------------------------------------------------------------------



#endif // cgGameMessage_h__
