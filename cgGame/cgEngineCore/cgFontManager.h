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

	// ��ʼ������Ҫ�Ǽ�������
	bool Initialize(cgRenderImpl * pkRenderImpl);

	// ��������
	cgFont* FindFont(cgID id);

	// ����
	unsigned GetFontNum();

	// �豸��ʧʱ�Ĵ���
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
