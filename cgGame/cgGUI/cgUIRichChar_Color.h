
#ifndef cgUIRichChar_Color_h__
#define cgUIRichChar_Color_h__

#include "cguirichchar.h"

class cgUIRichChar_Color :
	public cgUIRichChar
{
public:
	cgUIRichChar_Color(void);

	virtual void SetAttr(LPCTSTR attrName, LPCTSTR attrValue);
	virtual void Draw(cgUIRichPen & pen, int x, int y);
protected:
	cgColor m_uColor;
};

REGISTE_RICHCHAR_CREATOR(TEXT("color"), cgUIRichChar_Color)

// -------------------------------------------------------------------
class cgUIRichChar_ColorEnd:
	public cgUIRichChar
{
public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
};

REGISTE_RICHCHAR_CREATOR(TEXT("/color"), cgUIRichChar_ColorEnd)

#endif // cgUIRichChar_Color_h__