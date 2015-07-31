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

	// 设置
	void SetObject(cgGameObject * pkObj);

	// 给每个动作加一个名字，好区分一些
	void SetName(const string & strName);
	const string& GetName();

	// 获取action的持续时间
	float GetActionTime();

	// 开始
	void Start();

	// 停止
	void Stop();

	// 更新
	void Update(float fDeltaTime);

	// 是否完成
	bool IsStopped();

	// 是否激活
	bool IsActive();
protected:
	// 子类继承用，模板函数模式
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
