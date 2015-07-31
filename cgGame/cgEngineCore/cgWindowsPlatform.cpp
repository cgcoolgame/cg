#include "StdAfx.h"
#include "cgWindowsPlatform.h"
#include "cgD3DRenderImpl.h"
#include "cgFMODSoundPlayerImpl.h"
#include "cgWindow.h"


cgWindowsPlatform::cgWindowsPlatform(void)
{
}

cgRenderImpl * cgWindowsPlatform::CreateRenderImpl()
{
	return new cgD3DRenderImpl;
}

cgSoundPlayerImpl * cgWindowsPlatform::CreateSoundPlayerImpl()
{
	return new cgFMODSoundPlayerImpl;
}

cgWindow * cgWindowsPlatform::CreateAppWindow()
{
	return new cgWindow;
}
