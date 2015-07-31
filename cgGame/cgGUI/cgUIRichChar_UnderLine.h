#ifndef cgUIRichChar_UnderLine_h__
#define cgUIRichChar_UnderLine_h__


#include "cguirichchar.h"
class cgUIRichChar_UnderLine :
	public cgUIRichChar
{
public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
};

REGISTE_RICHCHAR_CREATOR(TEXT("underline"), cgUIRichChar_UnderLine)
// -------------------------------------------------------------------

class cgUIRichChar_UnderLineEnd :
	public cgUIRichChar
{
public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
};

REGISTE_RICHCHAR_CREATOR(TEXT("/underline"), cgUIRichChar_UnderLineEnd)
// -------------------------------------------------------------------


#endif // cgUIRichChar_UnderLine_h__
