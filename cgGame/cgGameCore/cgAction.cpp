#include "StdAfx.h"
#include "cgAction.h"
#include "cgGameApp.h"
#include "cgGameObject.h"

// ------------------------------------------------------------------------
#ifdef _DEBUG
//#define _DEBUG_LOG_ACTION_
#endif
// ------------------------------------------------------------------------
cgAction::cgAction(void)
{
	m_strName = "cgAction";
	m_pkObject = NULL;
	m_fActionTime = 0.0f;
	m_bIsStopped = false;
	m_bIsActive = false;
}

cgAction::~cgAction(void)
{
#ifdef _DEBUG_LOG_ACTION_
	if (m_pkObject)
	{
		string strLog = "<cgAction>:"+m_pkObject->GetName()+"."+GetName()+"->Destroyed !";
		cout<<strLog.c_str()<<endl;
	}
#endif
}

void cgAction::SetObject( cgGameObject * pkObj )
{
	m_pkObject = pkObj;
}

void cgAction::SetName( const string & strName )
{
	m_strName = strName;
}

const string& cgAction::GetName()
{
	return m_strName;
}

float cgAction::GetActionTime()
{
	return m_fActionTime;
}

void cgAction::Start( )
{
	m_bIsActive = true;
	DoStart();

#ifdef _DEBUG_LOG_ACTION_
	string strLog = "<cgAction>:"+m_pkObject->GetName()+"."+GetName()+"->Start !";
	cout<<strLog.c_str()<<endl;
#endif
}

void cgAction::DoStart()
{
}

void cgAction::Stop()
{
	m_bIsStopped = true;
	DoStop();

#ifdef _DEBUG_LOG_ACTION_
	string strLog = "<cgAction>:"+m_pkObject->GetName()+"."+GetName()+"->Stopped !";
	cout<<strLog.c_str()<<endl;
#endif
}

void cgAction::Update( float fDeltaTime )
{
	m_fActionTime += fDeltaTime;
	DoUpdate(fDeltaTime);
}
void cgAction::DoUpdate( float fDeltaTime )
{

}

bool cgAction::IsActive()
{
	return m_bIsActive;
}

bool cgAction::IsStopped()
{
	return m_bIsStopped;
}

void cgAction::DoStop()
{
}





