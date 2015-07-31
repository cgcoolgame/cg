#include "StdAfx.h"
#include "cgFontManager.h"
#include "cgFont.h"

cgFontManager::cgFontManager(void)
{
	m_pkRenderImpl = NULL;
	m_pFontList = NULL;
	m_uFontNum = 0;
}


cgFontManager::~cgFontManager(void)
{
	delete[] m_pFontList;
}

// ---------------------------------------------------------------------
bool cgFontManager::Initialize(cgRenderImpl * pkRenderImpl)
{
	assert(pkRenderImpl);

	m_pkRenderImpl = pkRenderImpl;
	return LoadFonts();
}

bool cgFontManager::LoadFonts()
{
	// 这里应该是跨平台比较蛋疼的地方
	// 后面做成可以配置的
	unsigned uNum = GetPrivateProfileInt(TEXT("Fonts"), TEXT("Num"), 0, TEXT("./Fonts/Fonts.ini") );

	if (uNum <= 0)
		return false;

	m_pFontList = new cgFont[uNum];

	cgFontConfig kConfig;
	TCHAR szAppName[CG_SHORT_TEXT_BUFF_LEN];
	for (unsigned i = 0; i < uNum; ++i)
	{
		cgSprintf(szAppName, CG_SHORT_TEXT_BUFF_LEN, TEXT("Font_%d"), i);

		kConfig.uSize = GetPrivateProfileInt(szAppName, TEXT("Size"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uHeight = GetPrivateProfileInt(szAppName, TEXT("Height"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uWidth = GetPrivateProfileInt(szAppName, TEXT("Width"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uWeight = GetPrivateProfileInt(szAppName, TEXT("Weight"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uMipLevels = GetPrivateProfileInt(szAppName, TEXT("MipLevels"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uItalic =  GetPrivateProfileInt(szAppName, TEXT("Italic"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uCharSet =  GetPrivateProfileInt(szAppName, TEXT("CharSet"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uOutputPrecision =  GetPrivateProfileInt(szAppName, TEXT("OutputPrecision"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uQuality =  GetPrivateProfileInt(szAppName, TEXT("Quality"), 0, TEXT("./Fonts/Fonts.ini"));
		kConfig.uPitchAndFamily = GetPrivateProfileInt(szAppName, TEXT("PitchAndFamily"), 0, TEXT("./Fonts/Fonts.ini"));

		GetPrivateProfileString(szAppName, TEXT("FaceName"), TEXT(""),
			kConfig.szFaceName, CG_SHORT_TEXT_BUFF_LEN, TEXT("./Fonts/Fonts.ini"));

		GetPrivateProfileString(szAppName, TEXT("Text"), TEXT(""),
			kConfig.szText, CG_SHORT_TEXT_BUFF_LEN, TEXT("./Fonts/Fonts.ini"));

		GetPrivateProfileString(szAppName, TEXT("Pic"), TEXT(""),
			kConfig.szPicPath, CG_SHORT_TEXT_BUFF_LEN, TEXT("./Fonts/Fonts.ini"));

		// 坑，如果width和height为零，则认为其大小和size一致 [3/11/2014 Administrator]
		if (kConfig.uSize == 0)
			kConfig.uSize = 12;

		if (kConfig.uWidth == 0)
			kConfig.uWidth = kConfig.uSize;

		if (kConfig.uHeight == 0)
			kConfig.uHeight = kConfig.uSize;

		cgFont & font = m_pFontList[m_uFontNum];
		if (!font.Initialize(m_pkRenderImpl, kConfig))
			return false;
		else
			++m_uFontNum;
	}

	return true;
}

cgFont* cgFontManager::FindFont( cgID id )
{
	if (id < m_uFontNum)
		return m_pFontList+id;
	
	return NULL;
}

unsigned cgFontManager::GetFontNum()
{
	return m_uFontNum;
}

bool cgFontManager::PreOnLostDevice()
{
	for (unsigned i = 0; i < GetFontNum(); ++i)
	{
		FindFont(i)->Reset();
	}
	return true;
}

bool cgFontManager::OnResetDevice()
{
	return true;
}
