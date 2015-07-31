#ifndef cgUIRichChar_Image_h__
#define cgUIRichChar_Image_h__


#include "cguirichchar.h"
#include "cgUIImage.h"

class cgUIRichChar_Image :
	public cgUIRichChar
{
public:
	cgUIRichChar_Image(void);

	virtual void SetAttr(LPCTSTR attrName, LPCTSTR attrValue);
	virtual cgSizeF GetCharSize(cgID font);
	virtual void Draw(cgUIRichPen & pen, int x, int y);

protected:
	cgUIImagePtr m_spImage;
};

REGISTE_RICHCHAR_CREATOR(TEXT("image"), cgUIRichChar_Image)

#endif // cgUIRichChar_Image_h__
