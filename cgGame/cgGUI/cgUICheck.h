#ifndef cgUICheck_h__
#define cgUICheck_h__

#include "cgUIWidget.h"

class cgUICheck :
	public cgUIWidget
{
public:
	cgUICheck(void);
	~cgUICheck(void);

public:

	// ��Ϣ����
	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

	// �Ƿ�ѡ
	bool IsChecked();
	void SetCheck(bool bChecked);

	// ����checkר����ͼƬ
	void SetCheckPic(LPCTSTR lpctNormal, LPCTSTR lpctChecked);
	void SetCheckPic(cgID idNormal, cgID idChecked);
	void SetCheckPic(cgUIImagePtr spNormal, cgUIImagePtr spChecked);

	// ������ɫ
	void SetCheckColor(cgColor normalColor, cgColor checkedColor);

protected:
	virtual void DrawBackPic(const cgRectF& clipRect);
	virtual void DrawBackground(const cgRectF& clipRect);

private:
	cgUIImagePtr m_spNormalPic;
	cgUIImagePtr m_spCheckedPic;
	cgColor m_uCheckedColor;
	bool m_bIsChecked;
};

#endif // cgUICheck_h__
