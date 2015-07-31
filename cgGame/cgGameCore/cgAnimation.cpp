#include "StdAfx.h"
#include "cgAnimation.h"


cgAnimation::cgAnimation(void)
{
	m_fFrequence = 1.0f;
	m_enmDir = cgDirectionEnumMax;
}

cgAnimation::~cgAnimation(void)
{
}

void cgAnimation::AddSequence( cgImageSequencePtr spSequence, cgDirectionEnum enmDir )
{
	if (spSequence && enmDir < cgDirectionEnumMax)
	{
		m_kSequenceList[enmDir] = spSequence;
		spSequence->SetVisible(false);
		AttachChild(&spSequence);
	}
}

cgImageSequencePtr cgAnimation::GetSequence( cgDirectionEnum enmDir )
{
	if (enmDir < cgDirectionEnumMax)
		return m_kSequenceList[enmDir];

	return NULL;
}

void cgAnimation::SetDirection( cgDirectionEnum enmDir )
{
	if (enmDir >= cgDirectionEnumMax || enmDir == m_enmDir)
		return;
	
	m_enmDir = enmDir;

	if (m_spCurSequence)
		m_spCurSequence->SetVisible(false);

	m_spCurSequence = GetSequence(m_enmDir);
	if (m_spCurSequence)
	{
		m_spCurSequence->Reset();
		m_spCurSequence->SetVisible(true);
		SetSize(m_spCurSequence->GetSize());
	}
	
}

cgImageSequencePtr cgAnimation::GetCurSequence()
{
	return m_spCurSequence;
}

cgDirectionEnum cgAnimation::GetDirection()
{
	return m_enmDir;
}

void cgAnimation::SetFrequence( float fFreq )
{
	m_fFrequence = fFreq;
}

float cgAnimation::GetFrequence()
{
	return m_fFrequence;
}

void cgAnimation::SetID( cgID id )
{
	m_id = id;
}

cgID cgAnimation::GetID()
{
	return m_id;
}
