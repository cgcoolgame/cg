#include "StdAfx.h"
#include "cgDestroy.h"
#include "cgGameObject.h"

cgDestroy::cgDestroy(void)
{
	m_strName = "cgDestroy";
}

void cgDestroy::DoStart()
{
	m_pkObject->Destroy();
}
