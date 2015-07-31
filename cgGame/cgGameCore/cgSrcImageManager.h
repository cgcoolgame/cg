
// ����Դ��һ�η�װ,
// ��֤һ��ͼƬֻ����һ��

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
	// ����ͼƬ
	cgImagePtr LoadImage(LPCTSTR lpctImagePath, bool bShare = true);

	// ���£�Ϊ��̭��׼��
	void Update(float fTime);

private:
	// ����ͼƬ
	cgImagePtr FindImage(LPCTSTR lpctImagePath);

private:
	cgImagePtrMap m_kImagePtrMap;
};

#endif // cgSrcImageManager_h__
