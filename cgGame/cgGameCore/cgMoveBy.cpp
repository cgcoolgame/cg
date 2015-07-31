#include "StdAfx.h"
#include "cgMoveBy.h"
#include "cgGameObject.h"
#include <cgMath.h>


cgMoveBy::cgMoveBy(void)
{
	m_strName = "cgMoveBy";
	m_fMoveTime = 0.0f;
}

cgMoveBy::cgMoveBy( float xMove, float yMove, float moveTime )
{
	m_strName = "cgMoveBy";
	m_kMoveBy.x = xMove;
	m_kMoveBy.y = yMove;
	m_fMoveTime = max(moveTime, cgMath::FLOAT_MIN);
	m_kLeftMoveBy = m_kMoveBy;
	m_kSpeed = m_kMoveBy/m_fMoveTime;
}

cgMoveBy::cgMoveBy( const cgVector& moveBy, float moveTime )
{
	m_strName = "cgMoveBy";
	m_kMoveBy = moveBy;
	m_fMoveTime = max(moveTime, cgMath::FLOAT_MIN);
	m_kLeftMoveBy = m_kMoveBy;
	m_kSpeed = m_kMoveBy/m_fMoveTime;
}

void cgMoveBy::DoUpdate( float fDeltaTime )
{
	cgVector deltaMove = m_kSpeed*fDeltaTime;
	if (m_kLeftMoveBy.Length() > deltaMove.Length())
	{
		m_pkObject->Move(deltaMove);
		m_kLeftMoveBy -= deltaMove;
	}else
	{
		m_pkObject->Move(m_kLeftMoveBy);
		Stop();
	}
}

cgMoveBy * cgMoveBy::FromSpeed( float xMove, float yMove, float moveSpeed )
{
	return cgMoveBy::FromSpeed(cgVector(xMove, yMove), moveSpeed);
}

cgMoveBy * cgMoveBy::FromSpeed( const cgVector& moveBy, float moveSpeed )
{
	float moveTime = moveBy.Length()/moveSpeed;
	return new cgMoveBy(moveBy, moveTime);
}
