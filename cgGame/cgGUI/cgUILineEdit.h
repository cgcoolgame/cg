//////////////////////////////////////////////////////////////////////////
// 最简单输入框，基本文本和密码
//////////////////////////////////////////////////////////////////////////

#ifndef cgUILineEdit_h__
#define cgUILineEdit_h__
#include "cgUIWidget.h"

class cgUILineEdit :
	public cgUIWidget
{
public:
	cgUILineEdit();
	cgUILineEdit(const string& strName);
	~cgUILineEdit(void);

public:
	void SetSelColor(cgColor color);
	cgColor GetSelColor();

	virtual bool OnMessage(UINT uMsg, unsigned wparam, unsigned lparam);
	virtual void UpdateSelf(float fTime);

	void SetEditType(enmUIEditType enmType);
	enmUIEditType GetEditStyle();

	virtual void SetText(LPCTSTR lpctText);

	void SetMaxCharNum(int nMax);
	int GetMaxCharNum();

	// 粘贴
	virtual bool OnPaste();

	// 复制
	virtual bool OnCopy();

	// 剪切， 
	virtual bool OnCut();

	virtual bool Insert(LPCTSTR lpctStr);

	virtual void OnMouseOut(unsigned wparam, unsigned lparam);

protected:

	bool IsCursorDrawable();

	bool OnKeyDown(unsigned wparam, unsigned lparam);
	bool OnChar(unsigned wparam, unsigned lparam);
	bool OnLButtonDown(unsigned wparam, unsigned lparam);
	bool OnMouseMove(unsigned wparam, unsigned lparam);
	bool EraseChar(int nCursorPos);
	bool ClearSel();

	int GetUICharWidth(TCHAR ch);
	cgSizeF GetUICharSize(TCHAR ch);

	bool IsPrintableWord(TCHAR ch);

	bool InsertChar(TCHAR ch);

	bool EnsureCursorVisible();

	// 如果bNear为true，则选中最近的一个index
	// 否则，只向前取整
	// 0: 最近
	// 1：向前
	// 2: 向后
	int XPointToCharIndex(int x, int nType = 0);
	int CharIndexToXPoint(int pos);

	bool SetCursorPos(int nPos);// 设置输入光标的位置
	bool SetSelBegin(int nPos);	// 设置选中起始点的位置

	bool KeyMoveCursor(int nDestPos); // 移动光标

protected:

	virtual void DrawText(const cgRectF& clipRect);

	void DrawScrollCaption(const cgRectF& clipRect, LPCTSTR lpctStr);

	void DrawSelBar(const cgRectF& clipRect);
	void DrawCursor();
private:
	enmUIEditType m_enmType;	// 是否是密码输入框
	float m_fLastUpdateTime;
	cgColor m_uSelBackColor;	// 选中的背景颜色
	int m_nCursorPos;		// 当前光标位置
	int m_nSelBegin;		// 选中字符的开始
	int m_nFirstVisibleCharIndex; // 绘制偏移，字符index偏移
	int m_nMaxCharNum;
	bool m_bCursorVisible;

};

#endif // cgUILineEdit_h__
