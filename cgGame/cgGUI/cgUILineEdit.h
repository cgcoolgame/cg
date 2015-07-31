//////////////////////////////////////////////////////////////////////////
// �������򣬻����ı�������
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

	// ճ��
	virtual bool OnPaste();

	// ����
	virtual bool OnCopy();

	// ���У� 
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

	// ���bNearΪtrue����ѡ�������һ��index
	// ����ֻ��ǰȡ��
	// 0: ���
	// 1����ǰ
	// 2: ���
	int XPointToCharIndex(int x, int nType = 0);
	int CharIndexToXPoint(int pos);

	bool SetCursorPos(int nPos);// �����������λ��
	bool SetSelBegin(int nPos);	// ����ѡ����ʼ���λ��

	bool KeyMoveCursor(int nDestPos); // �ƶ����

protected:

	virtual void DrawText(const cgRectF& clipRect);

	void DrawScrollCaption(const cgRectF& clipRect, LPCTSTR lpctStr);

	void DrawSelBar(const cgRectF& clipRect);
	void DrawCursor();
private:
	enmUIEditType m_enmType;	// �Ƿ������������
	float m_fLastUpdateTime;
	cgColor m_uSelBackColor;	// ѡ�еı�����ɫ
	int m_nCursorPos;		// ��ǰ���λ��
	int m_nSelBegin;		// ѡ���ַ��Ŀ�ʼ
	int m_nFirstVisibleCharIndex; // ����ƫ�ƣ��ַ�indexƫ��
	int m_nMaxCharNum;
	bool m_bCursorVisible;

};

#endif // cgUILineEdit_h__
