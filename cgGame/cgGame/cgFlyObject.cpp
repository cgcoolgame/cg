#include "StdAfx.h"
#include "cgFlyObject.h"
#include "cgRender.h"


cgFlyObject::cgFlyObject(void)
{
	m_nBoundWidth = 0;
	m_nBoundHeight = 0;
	m_enmCamp = cgFlyObjectCamp_None;
}


cgFlyObject::~cgFlyObject(void)
{
}


void cgFlyObject::Update( float fDetalTime )
{
	m_kPos += m_kDirection*m_nSpeed*fDetalTime;
}

void cgFlyObject::Render()
{
#ifdef _DEBUG
	cgRect box;
	GetBoundRect(box);
	if (GetCamp() == cgFlyObjectCamp_Self)
	{
		cgRender::Get()->FillRect(box, 0xff00ff00);
	}else
	{
		cgRender::Get()->FillRect(box, 0xffffffff);

	}
#endif
}

const cgVector& cgFlyObject::GetPosition() const
{
	return m_kPos;
}

void cgFlyObject::SetPosition( const cgVector& point )
{
	m_kPos = point;
}

void cgFlyObject::SetPosition( float x, float y )
{
	m_kPos.x = x;
	m_kPos.y = y;
}

int cgFlyObject::GetBoundWidth() const
{
	return m_nBoundWidth;
}

int cgFlyObject::GetBoundHeight() const
{
	return m_nBoundHeight;
}

void cgFlyObject::SetBound( int w, int h )
{
	m_nBoundWidth = w;
	m_nBoundHeight = h;
}

void cgFlyObject::GetBoundRect( cgRect & rect )
{
	rect.x = m_kPos.x-(m_nBoundWidth>>1);
	rect.y = m_kPos.y-(m_nBoundHeight>>1);
	rect.w = m_nBoundWidth;
	rect.h = m_nBoundHeight;
}


void cgFlyObject::SetCamp( cgFlyObjectCamp enmCamp )
{
	m_enmCamp = enmCamp;
}

cgFlyObjectCamp cgFlyObject::GetCamp()
{
	return m_enmCamp;
}

void cgFlyObject::Active()
{
	m_enmState = cgFlyObjectState_Active;
}

bool cgFlyObject::IsActive()
{
	return cgFlyObjectState_Active == m_enmState;
}

void cgFlyObject::SetDead()
{
	m_enmState = cgFlyObjectState_Dead;
}

bool cgFlyObject::IsDead()
{
	return m_enmState == cgFlyObjectState_Dead;
}

void cgFlyObject::SetInvalid()
{
	m_enmState = cgFlyObjectState_Invalid;
}

bool cgFlyObject::IsInvalid()
{
	return m_enmState == cgFlyObjectState_Invalid;
}

cgFlyObjectState cgFlyObject::GetState()
{
	return m_enmState ;
}

void cgFlyObject::Move( float x, float y )
{
	m_kPos.x += x;
	m_kPos.y += y;
}

float cgFlyObject::GetPosX()
{
	return m_kPos.x;
}

float cgFlyObject::GetPosY()
{
	return m_kPos.y;
}

int cgFlyObject::GetSpeed()
{
	return m_nSpeed;
}

void cgFlyObject::SetSpeed( int nSpeed )
{
	m_nSpeed = nSpeed;
}

void cgFlyObject::SetDirection( float x, float y )
{
	m_kDirection.x = x;
	m_kDirection.y = y;
	m_kDirection.Normalize();
}

void cgFlyObject::SetDirection( const cgVector& direction )
{
	m_kDirection = direction;
}

void cgFlyObject::GetDirection( float &x, float &y )
{
	x = m_kDirection.x;
	y = m_kDirection.y;
}

const cgVector& cgFlyObject::GetDirection()
{
	return m_kDirection;
}

