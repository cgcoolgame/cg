#include "StdAfx.h"
#include "cgRefObject.h"


cgRefObject::cgRefObject(void)
{
	m_uRefNum = 0;

#ifdef _DEBUG
	++ms_uTotalNum;
	m_uIncreaseNum = 0;
	m_uDecreaseNum = 0;
#endif
}


cgRefObject::~cgRefObject(void)
{
}

// --------------------------------------------------------
void cgRefObject::IncreaseRef()
{
#ifdef _DEBUG
		++m_uIncreaseNum;
		++ms_uTotalIncrease;
#endif

	++m_uRefNum;
}

void cgRefObject::DecreaseRef()
{
#ifdef _DEBUG
	++m_uDecreaseNum;
	++ms_uTotalDecrease;
#endif

	assert(m_uRefNum);
	if (--m_uRefNum <= 0)
	{
		DeleteThis();
	}
}

unsigned cgRefObject::GetRefNum() const
{
	return m_uRefNum;
}

void cgRefObject::DeleteThis()
{
#ifdef _DEBUG
	--ms_uTotalNum;
#endif
	delete this;
}


#ifdef _DEBUG

unsigned cgRefObject::GetIncreaseNum() const
{
	return m_uIncreaseNum;
}

unsigned cgRefObject::GetDecreaseNum() const
{
	return m_uDecreaseNum;
}

unsigned cgRefObject::GetTotalObjectNum()
{
	return ms_uTotalNum;
}

unsigned cgRefObject::GetTotalIncrease()
{
	return ms_uTotalIncrease;
}

unsigned cgRefObject::GetTotalDecrease()
{
	return ms_uTotalDecrease;
}

unsigned cgRefObject::ms_uTotalNum = 0;
unsigned cgRefObject::ms_uTotalIncrease = 0;
unsigned cgRefObject::ms_uTotalDecrease = 0;

#endif



