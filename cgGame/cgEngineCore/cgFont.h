
#ifndef cgFont_h__
#define cgFont_h__

#include "cgImage.h"


const unsigned CG_DEFAULT_FONT_TEXTURE_WITH = 512;		// 512*512的贴图
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

	// 重置
	void Reset();

	// 绘制一个字符
	void DrawChar(TCHAR ch, float x, float y, cgColor color, float scale = 1.0f);

	// 获取字体配置
	const cgFontConfig * GetConfig();

	// 获取一个字符的绘制宽度
	float GetCharWidthInPixel(TCHAR ch);

	// 获得一个字符的size
	cgSizeF GetCharSizeInPixel(TCHAR ch);
#ifdef _DEBUG
	void ShowSelf();
#endif

private:

	// 把一个字符渲染到纹理上
	cgImagePtr RenderCharToTexture(TCHAR ch);

	// 加载美术字
	bool LoadExtendTextureAndWords();

	// 查找wordImage
	cgImagePtr GetCharImage(TCHAR ch);
private:
	// 字体的配置
	cgFontConfig m_kConfig;

	// font和impl绑定
	cgRenderImpl * m_pkRenderImpl;

	// 字体id，逻辑字体在renderimpl里面对应的字体id
	cgID m_id;

	// 后台纹理的宽和高
	int m_nBkTexWidth;
	int m_nBkTexHeight;

	// 所有字体实际上是绘制到一个固定大小的贴图上的
	// 下一次绘制的时候就可以当做图片绘制了。
	cgImagePtr m_spBuffTexImg;

	float m_fBkTexXOff;	// 背景贴图用了多少了
	float m_fBkTexYOff;	// 同上

	// 美术字的贴图
	cgImagePtr m_spExtendTexImg;

	// 里面是每个字符对应的image，是referenceImage
	cgImagePtr m_spWordImageList[CG_MAX_WORD_PER_FONT];
};


#endif // cgFont_h__
