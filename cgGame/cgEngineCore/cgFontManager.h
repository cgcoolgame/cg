#ifndef cgFontManager_h__
#define cgFontManager_h__

#include "cgSingleton.h"

class cgFont;
class cgRenderImpl;

class cgFontManager:public cgSingleton<cgFontManager>
{
public:
	cgFontManager(void);
	virtual ~cgFontManager(void);
public:

	// 初始化，主要是加载字体
	bool Initialize(cgRenderImpl * pkRenderImpl);

	// 查找字体
	cgFont* FindFont(cgID id);

	// 个数
	unsigned GetFontNum();

	// 设备丢失时的处理
	bool PreOnLostDevice();
	bool OnResetDevice();

private:
	
	bool LoadFonts();

private:
	cgRenderImpl * m_pkRenderImpl;
	cgFont * m_pFontList;
	unsigned m_uFontNum;
};

#endif // cgFontManager_h__
