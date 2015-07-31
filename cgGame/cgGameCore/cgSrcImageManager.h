
// 对资源的一次封装,
// 保证一张图片只加载一次

#ifndef cgSrcImageManager_h__
#define cgSrcImageManager_h__

#include <map>
#include "cgImage.h"
#include "cgSingleton.h"

typedef std::map<cgString, cgImagePtr> cgImagePtrMap;

class cgSrcImageManager: public cgSingleton<cgSrcImageManager>
{
public:
	cgSrcImageManager(void);
	~cgSrcImageManager(void);
public:

	bool Initialize();
	// 加载图片
	cgImagePtr LoadImage(LPCTSTR lpctImagePath, bool bShare = true);

	// 更新，为淘汰做准备
	void Update(float fTime);

private:
	// 查找图片
	cgImagePtr FindImage(LPCTSTR lpctImagePath);

private:
	cgImagePtrMap m_kImagePtrMap;
};

#endif // cgSrcImageManager_h__
