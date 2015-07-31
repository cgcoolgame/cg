#include "StdAfx.h"
#include "cgSrcImageManager.h"


cgSrcImageManager::cgSrcImageManager(void)
{
}


cgSrcImageManager::~cgSrcImageManager(void)
{
	m_kImagePtrMap.clear();
}


bool cgSrcImageManager::Initialize()
{
	return true;
}

// -------------------------------------------------------------------------------

cgImagePtr cgSrcImageManager::LoadImage( LPCTSTR lpctImagePath, bool bShare )
{
	cgImagePtr ptr;

	if (!bShare)
	{
		// 不共享，就只有他自己在用了，不保存
		ptr = cgImage::LoadFromFile(lpctImagePath);
	}
	else
	{
		// 共享，就先查缓存，不存在就创建，并加入缓存
		ptr = FindImage(lpctImagePath);
		if (!ptr)
		{
			ptr = cgImage::LoadFromFile(lpctImagePath);
			m_kImagePtrMap[lpctImagePath] = ptr;
		}
	}

	return ptr;
}

cgImagePtr cgSrcImageManager::FindImage( LPCTSTR lpctImagePath )
{
	cgImagePtrMap::iterator it = m_kImagePtrMap.find(lpctImagePath);
	if (it != m_kImagePtrMap.end())
		return it->second;

	return NULL;
}

void cgSrcImageManager::Update( float fTime )
{
	// 什么都不做
}
