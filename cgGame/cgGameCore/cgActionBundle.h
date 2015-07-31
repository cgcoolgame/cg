#ifndef cgActionBundle_h__
#define cgActionBundle_h__


#include "cgaction.h"
class cgActionBundle :
	public cgAction
{
public:
	cgActionBundle(void);
	
	void Add(cgAction * pkAction);
	size_t GetSize();

protected:
	virtual void DoStart();
	virtual void DoUpdate(float fDeltaTime);

protected:
	cgActionPtrList m_kActionList;
};

#endif // cgActionBundle_h__
