
#ifndef cgUIRichChar_Link_h__
#define cgUIRichChar_Link_h__

#include "cguirichchar.h"
class cgUIRichChar_Link :
	public cgUIRichChar
{
public:
	cgUIRichChar_Link(void);
	~cgUIRichChar_Link(void);

	virtual void SetAttr(LPCTSTR attrName, LPCTSTR attrValue);
	virtual void Draw(cgUIRichPen & pen, int x, int y);

	virtual void OnMouseIn();
	virtual void OnMouseOut();
	virtual void OnMouseMove();
	virtual void OnLButtonDown();
	virtual void OnRButtonDown();
protected:
	cgString m_strFunc;
	cgString m_strParam;
	cgColor m_uColor;
	cgColor m_uHotColor;
	bool m_bIfUnderLine;
	bool m_bIfRClick;
	bool m_bIfHot;
	bool m_bIfUnderLineOnHot;
};

REGISTE_RICHCHAR_CREATOR(TEXT("link"), cgUIRichChar_Link)

// -------------------------------------------------------------------

class cgUIRichChar_LinkEnd:
	public cgUIRichChar
{
public:
	virtual void Draw(cgUIRichPen & pen, int x, int y);
};

REGISTE_RICHCHAR_CREATOR(TEXT("/link"), cgUIRichChar_LinkEnd)

#endif // cgUIRichChar_Link_h__
