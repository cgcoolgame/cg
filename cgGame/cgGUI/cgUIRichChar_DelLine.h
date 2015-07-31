#ifndef cgUIRichChar_DelLine_h__
#define cgUIRichChar_DelLine_h__


#include "cguirichchar.h"
class cgUIRichChar_DelLine :
	public cgUIRichChar
{
public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
};

REGISTE_RICHCHAR_CREATOR(TEXT("delline"), cgUIRichChar_DelLine)

// ---------------------------------------------------------------

class cgUIRichChar_DelLineEnd :
	public cgUIRichChar
{
public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
};

REGISTE_RICHCHAR_CREATOR(TEXT("/delline"), cgUIRichChar_DelLineEnd)

#endif // cgUIRichChar_DelLine_h__
