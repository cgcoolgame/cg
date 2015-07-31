#include "StdAfx.h"
#include "cgCamera.h"

cgCamera * cgCamera::ms_pkCurCamera = NULL;
cgCamera::cgCamera(void)
{
}


cgCamera::~cgCamera(void)
{
}

cgCamera * cgCamera::GetRenderCamera()
{
	return ms_pkCurCamera;
}

cgCamera * cgCamera::SetRenderCamera( cgCamera * pkCamera )
{
	cgCamera * pkOld = ms_pkCurCamera;
	ms_pkCurCamera = pkCamera;
	return pkOld;
}
