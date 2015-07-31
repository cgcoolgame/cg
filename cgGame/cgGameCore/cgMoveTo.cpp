#include "StdAfx.h"
#include "cgMoveTo.h"
#include "cgGameObject.h"
#include <cgMath.h>


cgMoveTo::cgMoveTo()
{
	m_strName = "cgMoveTo";
}

cgMoveTo::cgMoveTo( const cgVector& dest, float moveTime )
{
	m_strName = "cgMoveTo";
	m_kDest = dest;
	m_fMoveTime = max(moveTime, cgMath::FLOAT_MIN);
}

cgMoveTo::cgMoveTo( float xDest, float yDest, float moveTime )
{
	m_strName = "cgMoveTo";
	m_kDest.x = xDest;
	m_kDest.y = yDest;
	m_fMoveTime = max(moveTime, cgMath::FLOAT_MIN);
}

void cgMoveTo::DoStart()
{
	m_kMoveBy = m_kDest - m_pkObject->GetWorldPosition();
	m_kLeftMoveBy = m_kMoveBy;
	m_kSpeed = m_kMoveBy/m_fMoveTime;
}
