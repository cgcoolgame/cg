
//////////////////////////////////////////////////////////////////////////
// 富文本，字符定义
//////////////////////////////////////////////////////////////////////////

#ifndef cgUIRichChar_h__
#define cgUIRichChar_h__
#include <cgRefObject.h>
#include <cgSmartPointer.h>
#include "cgUIRichPen.h"
#include "cgUIRichCharSpawner.h"


class cgUIRichChar:
	public cgRefObject
{
public:
	cgUIRichChar(void);
	virtual ~cgUIRichChar(void);

public:
	void SetTypeString(const cgString & strType);
	const cgString & GetTypeString();

	virtual void SetAttr(LPCTSTR attrName, LPCTSTR attrValue);
	virtual void Draw(cgUIRichPen & pen, int x, int y);
	virtual void Measure(cgUIRichPen & pen);

	LPCTSTR GetRawString();
	void SetRawString(LPCTSTR rawStr);

	virtual cgSizeF GetCharSize(cgID font);

	virtual bool NeedChangeLine();

	virtual void OnMouseIn();
	virtual void OnMouseOut();
	virtual void OnMouseMove();
	virtual void OnLButtonDown();
	virtual void OnRButtonDown();

protected:
	cgString m_strType;
	cgString m_strRawString;
};

typedef cgSmartPointer<cgUIRichChar> cgUIRichCharPtr;


#endif // cgUIRichChar_h__
