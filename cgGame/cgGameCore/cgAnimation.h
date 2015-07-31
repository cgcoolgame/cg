#ifndef cgAnimation_h__
#define cgAnimation_h__

#include "cgImageSequence.h"

// �򵥵�֡��������

// ----------------------------------------------------------------
// ����������ʱ֧���ĸ�����
enum cgDirectionEnum
{
	cgFront ,			
	cgLeft ,
	cgRight,
	cgBack,
	cgFrontLeft,
	cgFrontRight,
	cgBackLeft,
	cgBackRight,
	cgDirectionEnumMax,
};

// ����
class cgAnimation:
	public cgGameObject
{
public:
	cgAnimation(void);
	~cgAnimation(void);

	// ÿ����������һ��id������ȫ��Ψһ�������ڵ�ǰ�����飨һ����ɫ��Ψһ
	void SetID(cgID id);
	cgID GetID();

	// ���һ������֡
	void AddSequence(cgImageSequencePtr spSequence, cgDirectionEnum enmDir);
	cgImageSequencePtr GetSequence(cgDirectionEnum enmDir);

	// ���õ�ǰ�ķ���
	void SetDirection(cgDirectionEnum enmDir);
	cgDirectionEnum GetDirection();

	// ��ȡ��ǰ����֡
	cgImageSequencePtr GetCurSequence();

	// ����Ƶ��
	void SetFrequence(float fFreq);
	float GetFrequence();

protected:
	cgImageSequencePtr m_kSequenceList[cgDirectionEnumMax];
	cgImageSequencePtr m_spCurSequence;

	cgDirectionEnum m_enmDir;
	cgID m_id;
	float m_fFrequence;	// Ƶ�ʣ�Ĭ��Ϊ1.0f
};

typedef cgSmartPointer<cgAnimation> cgAnimationPtr;
#endif // cgAnimation_h__
