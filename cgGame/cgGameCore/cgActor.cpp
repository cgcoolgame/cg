#include "StdAfx.h"
#include "cgActor.h"


cgActor::cgActor(void)
{
	m_enmDir =  cgRight;
}


cgActor::~cgActor(void)
{
}


void cgActor::AddAnimation( cgAnimationPtr spAnimation )
{
	if (spAnimation)
	{
		m_kAnimationMap[spAnimation->GetID()] = spAnimation;
		spAnimation->SetVisible(false);
		AttachChild(&spAnimation);
	}
}

cgAnimationPtr cgActor::GetAnimation( cgID id )
{
	cgAnimationPtrMap::iterator it = m_kAnimationMap.find(id);
	if (it != m_kAnimationMap.end())
		return it->second;

	return NULL;
}

void cgActor::SetCurAnimation( cgID id )
{
	if (m_spCurAnimation && m_spCurAnimation->GetID() == id)
		return ;

	if (m_spCurAnimation)
		m_spCurAnimation->SetVisible(false);

	m_spCurAnimation = GetAnimation(id);
	if (m_spCurAnimation)
	{
		m_spCurAnimation->SetVisible(true);
		m_spCurAnimation->SetDirection(m_enmDir);
		SetSize(m_spCurAnimation->GetSize());
	}
}

void cgActor::SetDirection( cgDirectionEnum enmDir )
{
	if (enmDir >= cgDirectionEnumMax)
		return;
	m_enmDir = enmDir;

	if (m_spCurAnimation)
		m_spCurAnimation->SetDirection(m_enmDir);
}

cgDirectionEnum cgActor::GetDirection()
{
	return m_enmDir;
}