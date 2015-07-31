#include "StdAfx.h"
#include "cgRotateTo.h"
#include "cgGameObject.h"
#include <cgMath.h>

cgRotateTo::cgRotateTo(void)
{
	m_strName = "cgRotateTo";
}

cgRotateTo::cgRotateTo( float rotateTo, float rotateTime )
{
	m_strName = "cgRotateTo";
	m_fRotateTo = rotateTo;
	m_fRotateTime = max(rotateTime, cgMath::FLOAT_MIN);
}

void cgRotateTo::DoStart()
{
	m_fRotateBy = m_fRotateTo - m_pkObject->GetWorldRotation();
	m_fLeftRotateBy = m_fRotateBy;
	m_fRotateSpeed = m_fRotateBy/m_fRotateTime;
}
