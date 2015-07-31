#ifndef cgUIRichPen_h__
#define cgUIRichPen_h__
#include <stack>
using namespace std;

class cgUIRichPen
{
public:
	cgUIRichPen(void);
	~cgUIRichPen(void);

// ------------------------------------------------------------------

	// 默认绘制颜色
	void SetDefaultColor(cgColor color);
	cgColor GetDefaultColor();

	// 当前颜色
	cgColor GetCurColor();
	void PushColor(cgColor color);
	void PopColor();

// ------------------------------------------------------------------
	void SetDefaultFont(cgID font);
	cgID GetDefaultFont();
	void PushFont(cgID font);
	void PopFont();
	cgID GetCurFont();
// ------------------------------------------------------------------
	void SetDefaultDrawUnderLine(bool bDraw);
	bool IfDefaultDrawUnderLine();
	void PushUnderLine(bool bUnderLine = true);
	void PopUnderLine();
	bool IfDrawUnderLine();
// ------------------------------------------------------------------
	void SetDefaultDrawDelLine(bool bDraw);
	bool IfDefaultDrawDelLine();
	void PushDelLine(bool bDelLine = true);
	void PopDelLine();
	bool IfDrawDelLine();

private:
	cgColor m_uDefaultColor;
	stack<cgColor> m_kColorStack;

	cgID m_idDefaultFont;
	stack<cgID> m_kFontStack;

	bool m_bIfDefaultDrawUnderLine;
	stack<bool> m_kDrawUnderLineStack;

	bool m_bIfDefaultDrawDelLine;
	stack<bool> m_kDrawDelLineStack;
};

#endif // cgUIRichPen_h__
