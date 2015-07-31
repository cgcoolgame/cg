#ifndef cgUIRichChar_Font_h__
#define cgUIRichChar_Font_h__

#include "cguirichchar.h"

class cgUIRichChar_Font :
	public cgUIRichChar
{
public:
	cgUIRichChar_Font(void);

	virtual void SetAttr(LPCTSTR attrName, LPCTSTR attrValue);
	virtual void Draw(cgUIRichPen & pen, int x, int y);
	virtual void Measure(cgUIRichPen & pen);
protected:
	cgID m_idFont;
};

REGISTE_RICHCHAR_CREATOR(TEXT("font"), cgUIRichChar_Font)

// -------------------------------------------------------------------
class cgUIRichChar_FontEnd:
	public cgUIRichChar
{
public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
	virtual void Measure(cgUIRichPen & pen);
};

REGISTE_RICHCHAR_CREATOR(TEXT("/font"), cgUIRichChar_FontEnd)

#endif // cgUIRichChar_Font_h__
