#include "StdAfx.h"
#include "cgDeactive.h"
#include "cgGameObject.h"

cgDeactive::cgDeactive(void)
{
}

void cgDeactive::DoStart()
{
	m_pkObject->SetActive(false);
}
