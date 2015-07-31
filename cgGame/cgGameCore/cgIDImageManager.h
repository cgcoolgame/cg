// ��id��ȷ��һ��ͼƬ��Դ
// ���ںϲ��õĸ���ͼƬ��Դ
// ����Ҫ�õ�cgSrcImageManager
// ���Ա�����cgSrcImageManager��ʼ���Ժ����ʹ��
#ifndef cgIDImageManager_h__
#define cgIDImageManager_h__
#include <map>
#include "cgSingleton.h"
#include "cgImage.h"

typedef struct tagIDImageConfig
{
	cgID id;	// �������˵��
	int x;		// x,y�����ڴ�ͼ�ϵ�ƫ��
	int y;		
	int w;		// ��ͼƬ�Ŀ�͸�
	int h;
	cgString path;	// ������ͼ��·��
}cgIDImageConfig;

typedef std::map<cgID, cgIDImageConfig*> cgIDImageConfigPtrMap;
typedef std::map<cgID, cgImagePtr> cgIDImagePtrMap;

class cgIDImageManager:public cgSingleton<cgIDImageManager>
{
public:
	cgIDImageManager(void);
	~cgIDImageManager(void);

	bool Initialize();
public:

	// ��ȡ���ø���
	unsigned GetConfigNum();

	// ��������
	cgIDImageConfig * FindConfig(cgID id);

	// ����ͼƬ
	cgImagePtr GetImage(cgID id);

private:
	// ��������
	bool LoadConfig();

private:
	cgIDImageConfigPtrMap m_kConfigPtrMap;
	cgIDImagePtrMap	m_kIDImagePtrMap;
};

#endif // cgIDImageManager_h__
