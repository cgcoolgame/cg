// 用id来确定一个图片资源
// 用于合并好的各种图片资源
// 它需要用到cgSrcImageManager
// 所以必须在cgSrcImageManager初始化以后才能使用
#ifndef cgIDImageManager_h__
#define cgIDImageManager_h__
#include <map>
#include "cgSingleton.h"
#include "cgImage.h"

typedef struct tagIDImageConfig
{
	cgID id;	// 这个不用说了
	int x;		// x,y就是在大图上的偏移
	int y;		
	int w;		// 子图片的宽和高
	int h;
	cgString path;	// 所属大图的路径
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

	// 获取配置个数
	unsigned GetConfigNum();

	// 查找配置
	cgIDImageConfig * FindConfig(cgID id);

	// 查找图片
	cgImagePtr GetImage(cgID id);

private:
	// 加载配置
	bool LoadConfig();

private:
	cgIDImageConfigPtrMap m_kConfigPtrMap;
	cgIDImagePtrMap	m_kIDImagePtrMap;
};

#endif // cgIDImageManager_h__
