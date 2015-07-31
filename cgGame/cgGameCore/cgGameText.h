#ifndef cgGameText_h__
#define cgGameText_h__


#include "cggameobject.h"
class cgGameText :
	public cgGameObject
{
public:
	cgGameText(void);
	cgGameText(const string & strName);
	cgGameText(const cgString& text, cgID font = 0, cgColor color = 0xffffffff, int style = DT_CENTER|DT_VCENTER);

	void SetText(cgString text);
	const cgString& GetText()const;

	void SetFont(cgID font);
	cgID GetFont()const;

	void SetTextStyle(int nStyle);
	int GetTextStyle()const;

	cgColor GetBackColor();
	void SetBackColor(cgColor color);

protected:
	virtual void DoRenderSelf(cgCamera * renderCamera);

protected:
	cgString m_strText;
	cgColor m_uBackColor;
	int m_nTextStyle;
	cgID m_idFont;
};

typedef cgSmartPointer<cgGameText> cgGameTextPtr;

#endif // cgGameText_h__
