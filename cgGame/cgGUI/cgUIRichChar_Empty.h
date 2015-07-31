#ifndef cgUIRichChar_Empty_h__
#define cgUIRichChar_Empty_h__

#include "cguirichchar.h"
class cgUIRichChar_Empty :
	public cgUIRichChar
{
public:
	cgUIRichChar_Empty();

	virtual void SetAttr(LPCTSTR attrName, LPCTSTR attrValue);
	virtual cgSizeF GetCharSize(cgID font);

protected:
	int m_nWidth;
	int m_nHeight;
};

REGISTE_RICHCHAR_CREATOR(TEXT("empty"), cgUIRichChar_Empty)

#endif // cgUIRichChar_Empty_h__
