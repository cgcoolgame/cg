
#ifndef cgActionSequence_h__
#define cgActionSequence_h__

#include "cgaction.h"
class cgActionSequence :
	public cgAction
{
public:
	cgActionSequence(void);

	void Add(cgAction * pkAction);

	size_t GetSize();

	

protected:
	virtual void DoStart();
	virtual void DoUpdate(float fDeltaTime);

	void Next();

protected:
	cgActionPtrList m_kActionList;
	cgActionPtr m_spCurAction;
};

#endif // cgActionSequence_h__
