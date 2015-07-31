#ifndef cgUIChar_h__
#define cgUIChar_h__
#include "cgUIRichChar.h"

class cgUIChar:
	public cgUIRichChar
{
public:
	cgUIChar(void);
	~cgUIChar(void);

public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
	virtual cgSizeF GetCharSize(cgID font);
};

REGISTE_RICHCHAR_CREATOR(TEXT(""), cgUIChar)

#endif // cgUIChar_h__
