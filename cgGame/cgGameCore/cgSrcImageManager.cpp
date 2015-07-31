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
		// ��������ֻ�����Լ������ˣ�������
		ptr = cgImage::LoadFromFile(lpctImagePath);
	}
	else
	{
		// �������Ȳ黺�棬�����ھʹ����������뻺��
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
	// ʲô������
}
