#include "StdAfx.h"
#include "cgMove.h"
#include "cgGameObject.h"


cgMove::cgMove(void)
{
	m_strName = "cgMove";
}

cgMove::cgMove( float xSpeed, float ySpeed )
{
	m_strName = "cgMove";
	SetSpeed(xSpeed, ySpeed);
}

cgMove::cgMove( const cgVector& speed )
{
	m_strName = "cgMove";
	SetSpeed(speed);
}

const cgVector& cgMove::SetSpeed( const cgVector& speed )
{
	m_kSpeed = speed;
	return m_kSpeed;
}

const cgVector& cgMove::SetSpeed( float xSpeed, float ySpeed )
{
	m_kSpeed.x = xSpeed;
	m_kSpeed.y = ySpeed;
	return m_kSpeed;
}

const cgVector& cgMove::GetSpeed() const
{
	return m_kSpeed;
}

void cgMove::DoUpdate( float fDeltaTime )
{
	m_pkObject->Move(m_kSpeed*fDeltaTime);
}
