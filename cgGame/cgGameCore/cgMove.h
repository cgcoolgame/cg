
#ifndef cgMove_h__
#define cgMove_h__

#include "cgaction.h"

// ��������ƶ������Ǹ���һ���ٶȣ����һֱ�ƶ�ȥ��
class cgMove :
	public cgAction
{
public:
	cgMove();
	cgMove(const cgVector& speed);
	cgMove(float xSpeed, float ySpeed);

	// �����ٶȣ����Զ�̬�ı���
	const cgVector& SetSpeed(const cgVector& speed);
	const cgVector& SetSpeed(float xSpeed, float ySpeed);
	const cgVector& GetSpeed()const;

protected:
	// ����
	virtual void DoUpdate(float fDeltaTime);

protected:
	cgVector m_kSpeed;
};

typedef cgSmartPointer<cgMove> cgMovePtr;
#endif // cgMove_h__
