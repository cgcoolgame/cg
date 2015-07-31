#include "StdAfx.h"
#include "cgRotate.h"
#include "cgGameObject.h"

cgRotate::cgRotate(void)
{
	m_strName = "cgRotate";
	m_fRotateSpeed = 0.0f;
}

cgRotate::cgRotate( float rotateSpeed )
{
	m_strName = "cgRotate";
	m_fRotateSpeed = rotateSpeed;
}

void cgRotate::SetRotateSpeed( float speed )
{
	m_fRotateSpeed = speed;
}

float cgRotate::GetRotateSpeed()
{
	return m_fRotateSpeed;
}

void cgRotate::DoUpdate( float fDeltaTime )
{
	m_pkObject->Rotate(fDeltaTime*m_fRotateSpeed);
}
