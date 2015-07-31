#include "StdAfx.h"
#include "cgRotateAround.h"
#include "cgGameObject.h"

cgRotateAround::cgRotateAround(void)
{
	m_strName = "cgRotateAround";
	m_fRotateSpeed = 0.0f;
}

cgRotateAround::cgRotateAround( float rotateSpeed, const cgVector& rotateCenter )
{
	m_strName = "cgRotateAround";
	m_fRotateSpeed = rotateSpeed;
	m_kRotateCenter = rotateCenter;
}

cgRotateAround::cgRotateAround( float rotateSpeed, float centerX, float centerY )
{
	m_strName = "cgRotateAround";
	m_fRotateSpeed = rotateSpeed;
	m_kRotateCenter.x = centerX;
	m_kRotateCenter.y = centerY;
}

void cgRotateAround::SetRotateSpeed( float rotateSpeed )
{
	m_fRotateSpeed = rotateSpeed;
}

float cgRotateAround::GetRotateSpeed()
{
	return m_fRotateSpeed;
}

void cgRotateAround::SetRotateCenter( const cgVector& rotateCenter )
{
	m_kRotateCenter = rotateCenter;
}

const cgVector & cgRotateAround::GetRotateCenter()
{
	return m_kRotateCenter;
}

void cgRotateAround::DoUpdate( float fDeltaTime )
{
	m_pkObject->RotateAround(m_fRotateSpeed*fDeltaTime, m_kRotateCenter);
}
