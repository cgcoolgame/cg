#ifndef cgUIRichChar_EndLine_h__
#define cgUIRichChar_EndLine_h__


#include "cguirichchar.h"
class cgUIRichChar_EndLine :
	public cgUIRichChar
{
public:
	virtual bool NeedChangeLine();
};

REGISTE_RICHCHAR_CREATOR(TEXT("endl"), cgUIRichChar_EndLine)

#endif // cgUIRichChar_EndLine_h__
