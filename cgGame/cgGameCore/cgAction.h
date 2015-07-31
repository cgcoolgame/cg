#ifndef cgAction_h__
#define cgAction_h__

#include <list>
#include "cgrefobject.h"
#include "cgSmartPointer.h"

class cgGameObject;

class cgAction;
typedef cgSmartPointer<cgAction> cgActionPtr;
typedef std::list<cgActionPtr> cgActionPtrList;

class cgAction:
	public cgRefObject
{
public:
	cgAction(void);
	~cgAction(void);

	// ����
	void SetObject(cgGameObject * pkObj);

	// ��ÿ��������һ�����֣�������һЩ
	void SetName(const string & strName);
	const string& GetName();

	// ��ȡaction�ĳ���ʱ��
	float GetActionTime();

	// ��ʼ
	void Start();

	// ֹͣ
	void Stop();

	// ����
	void Update(float fDeltaTime);

	// �Ƿ����
	bool IsStopped();

	// �Ƿ񼤻�
	bool IsActive();
protected:
	// ����̳��ã�ģ�庯��ģʽ
	virtual void DoStart();
	virtual void DoStop();
	virtual void DoUpdate(float fDeltaTime);

protected:
	cgGameObject * m_pkObject;
	string m_strName;

	float m_fActionTime;

	bool m_bIsStopped;
	bool m_bIsActive;
};

#endif // cgAction_h__
