#include "StdAfx.h"
#include "cgIDImageManager.h"
#include "cgSrcImageManager.h"
#include "cgTxtDataReader.h"
#include "..\cgEngineCore\cgStringTable.h"


cgIDImageManager::cgIDImageManager(void)
{
	LoadConfig();
}


cgIDImageManager::~cgIDImageManager(void)
{
	cgIDImageConfigPtrMap::iterator it = m_kConfigPtrMap.begin();
	for (; it != m_kConfigPtrMap.end(); ++it)
		delete it->second;
	
	m_kConfigPtrMap.clear();
}


bool cgIDImageManager::Initialize()
{
	return true;
}

// ------------------------------------------------------------
bool cgIDImageManager::LoadConfig()
{
	cgTxtDataReader kReader;

	if (!kReader.Open("./config/id_images.txt"))
		return false;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgIDImageConfig * pkConfig = new cgIDImageConfig;
		memset(pkConfig, 0, sizeof(cgIDImageConfig));

		int index = 0;
		pkConfig->id = atoi(pkRecord->GetField(index++));
		pkConfig->x = atoi(pkRecord->GetField(index++));
		pkConfig->y = atoi(pkRecord->GetField(index++));
		pkConfig->w = atoi(pkRecord->GetField(index++));
		pkConfig->h = atoi(pkRecord->GetField(index++));
		pkConfig->path = cgXConfigStr2CgTxt((pkRecord->GetField(index++)));

		m_kConfigPtrMap[pkConfig->id] = pkConfig;
	}
	return true;
}

unsigned cgIDImageManager::GetConfigNum()
{
	return m_kConfigPtrMap.size();
}

cgIDImageConfig * cgIDImageManager::FindConfig( cgID id )
{
	cgIDImageConfigPtrMap::iterator it = m_kConfigPtrMap.find(id);
	if (it != m_kConfigPtrMap.end())
		return it->second;

	return NULL;
}

cgImagePtr cgIDImageManager::GetImage( cgID id )
{
	cgIDImagePtrMap::iterator it = m_kIDImagePtrMap.find(id);
	if (it != m_kIDImagePtrMap.end())
		return it->second;

	cgIDImageConfig * pkConfig = FindConfig(id);
	if (!pkConfig)
		return NULL;

	// 找到了直接返回，没找到？
	cgImagePtr spImage = cgSrcImageManager::Get()->LoadImage(pkConfig->path.c_str());
	if (!spImage)
		return NULL;

	cgImagePtr spIDImage = cgImage::ClipFromImage(spImage, 
		cgRectF(pkConfig->x, pkConfig->y, pkConfig->w, pkConfig->h));

	m_kIDImagePtrMap[id] = spIDImage;

	return spIDImage;
}
