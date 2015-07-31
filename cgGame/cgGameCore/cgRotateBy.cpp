#include "StdAfx.h"
#include "cgRotateBy.h"
#include "cgGameObject.h"
#include <cgMath.h>

cgRotateBy::cgRotateBy(void)
{
	m_strName = "cgRotateBy";
	m_fRotateBy = 0.0f;
	m_fLeftRotateBy = 0.0f;
	m_fRotateTime = 0.0f;
	m_fRotateSpeed = 0.0f;
}

cgRotateBy::cgRotateBy( float rotateBy, float rotateTime )
{
	m_strName = "cgRotateBy";
	m_fRotateBy = rotateBy;
	m_fLeftRotateBy = m_fRotateBy;
	m_fRotateTime = max(rotateTime, cgMath::FLOAT_MIN);
	m_fRotateSpeed = m_fRotateBy/m_fRotateTime;
}

void cgRotateBy::DoUpdate( float fDeltaTime )
{
	float deltaRotate = fDeltaTime*m_fRotateSpeed;
	if (abs(m_fLeftRotateBy) > abs(deltaRotate))
	{
		m_pkObject->Rotate(deltaRotate);
		m_fLeftRotateBy -= deltaRotate;
	}else
	{
		m_pkObject->Rotate(m_fLeftRotateBy);
		Stop();
	}
}
