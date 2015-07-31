#include "StdAfx.h"
#include "cgUIRichCharSpawner.h"

int cgUIRichCharSpawner::ms_CreatorNum = 0;
cgUIRichCharCreator* cgUIRichCharSpawner::ms_kCreatorList[MAX_UI_RICH_CHAR_CREATOR_NUM];

void cgUIRichCharSpawner::Register( cgUIRichCharCreator * pCreator )
{
	if (ms_CreatorNum < MAX_UI_RICH_CHAR_CREATOR_NUM)
		ms_kCreatorList[ms_CreatorNum++] = pCreator;
}

cgUIRichChar * cgUIRichCharSpawner::Spawn( const cgString& strType )
{
	cgUIRichCharCreator * pkCreator = FindCreator(strType);
	return pkCreator?pkCreator->Create() : NULL;
}

cgUIRichCharCreator * cgUIRichCharSpawner::FindCreator( const cgString& strType )
{
	for (int i = 0; i < ms_CreatorNum; ++i)
	{
		if (ms_kCreatorList[i]->GetTypeString() == strType)
		{
			return ms_kCreatorList[i];
		}
	}

	return NULL;
}
