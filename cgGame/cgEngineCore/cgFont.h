
#ifndef cgFont_h__
#define cgFont_h__

#include "cgImage.h"


const unsigned CG_DEFAULT_FONT_TEXTURE_WITH = 512;		// 512*512����ͼ
const unsigned CG_DEFAULT_FONT_TEXTURE_HEIGHT = 512;
const unsigned CG_MAX_WORD_PER_FONT	= (unsigned short)-1;

class cgRenderImpl;

class cgFont
{
public:
	cgFont();
	virtual ~cgFont(void);

public:
	bool Initialize(cgRenderImpl * pkRenderImpl, const cgFontConfig & kConfig);

	// ����
	void Reset();

	// ����һ���ַ�
	void DrawChar(TCHAR ch, float x, float y, cgColor color, float scale = 1.0f);

	// ��ȡ��������
	const cgFontConfig * GetConfig();

	// ��ȡһ���ַ��Ļ��ƿ��
	float GetCharWidthInPixel(TCHAR ch);

	// ���һ���ַ���size
	cgSizeF GetCharSizeInPixel(TCHAR ch);
#ifdef _DEBUG
	void ShowSelf();
#endif

private:

	// ��һ���ַ���Ⱦ��������
	cgImagePtr RenderCharToTexture(TCHAR ch);

	// ����������
	bool LoadExtendTextureAndWords();

	// ����wordImage
	cgImagePtr GetCharImage(TCHAR ch);
private:
	// ���������
	cgFontConfig m_kConfig;

	// font��impl��
	cgRenderImpl * m_pkRenderImpl;

	// ����id���߼�������renderimpl�����Ӧ������id
	cgID m_id;

	// ��̨����Ŀ�͸�
	int m_nBkTexWidth;
	int m_nBkTexHeight;

	// ��������ʵ�����ǻ��Ƶ�һ���̶���С����ͼ�ϵ�
	// ��һ�λ��Ƶ�ʱ��Ϳ��Ե���ͼƬ�����ˡ�
	cgImagePtr m_spBuffTexImg;

	float m_fBkTexXOff;	// ������ͼ���˶�����
	float m_fBkTexYOff;	// ͬ��

	// �����ֵ���ͼ
	cgImagePtr m_spExtendTexImg;

	// ������ÿ���ַ���Ӧ��image����referenceImage
	cgImagePtr m_spWordImageList[CG_MAX_WORD_PER_FONT];
};


#endif // cgFont_h__
