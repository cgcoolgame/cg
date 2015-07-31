
#ifndef cgAnimationManager_h__
#define cgAnimationManager_h__

// һ������������
// һ����ɫ�������кܶ��鶯�����
// ÿ�������в�ͬ�ı�ʶ������Ϸ�и���
// ��Ҫ���Ŷ�Ӧ�Ķ�������֡

#include "cgAnimation.h"
#include <map>

// ���õĽ�ɫ����ö��
enum cgActorAction
{
	cgActorAction_Idle,			// Ĭ�Ͽ���״̬��վ��
	cgActorAction_Walk,			// ���ߣ�����
	cgActorAction_Run,			// �ܲ�������
	cgActorAction_SitDown,		// ����(���̣�
	cgActorAction_Sit,			// ���£�״̬��
	cgActorAction_Jump,			// ��
	cgActorAction_Fly,			// ����
	cgActorAction_Attack,		// ������Ĭ�Ϲ�������
	cgActorAction_Hurt,			// ������
	cgActorAction_Sing,			// Ĭ����������
	cgActorAction_Cast,			// Ĭ���ͷŶ�������������������Ҳ���������ͷŶ���
	cgActorAction_Die,			// ���������̣�
	cgActorAction_Dead,			// ��������ʬ��

};


typedef std::map<cgID , cgAnimationPtr> cgAnimationPtrMap;

class cgActor:
	public cgGameObject
{
public:
	cgActor(void);
	~cgActor(void);

	// ���һ�鶯��
	void AddAnimation(cgAnimationPtr spAnimation);
	cgAnimationPtr GetAnimation(cgID id);

	// ���õ�ǰ������
	void SetDirection(cgDirectionEnum enmDir);
	cgDirectionEnum GetDirection();

	// ���õ�ǰ�Ķ���
	void SetCurAnimation(cgID id);
	cgAnimationPtr GetCurAnimation();

protected:
	cgAnimationPtrMap m_kAnimationMap;
	cgAnimationPtr m_spCurAnimation;
	cgDirectionEnum m_enmDir;
};

typedef cgSmartPointer<cgActor> cgActorPtr;
#endif // cgAnimationManager_h__
