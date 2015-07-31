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

	// 消息处理
	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

	// 是否勾选
	bool IsChecked();
	void SetCheck(bool bChecked);

	// 设置check专属的图片
	void SetCheckPic(LPCTSTR lpctNormal, LPCTSTR lpctChecked);
	void SetCheckPic(cgID idNormal, cgID idChecked);
	void SetCheckPic(cgUIImagePtr spNormal, cgUIImagePtr spChecked);

	// 设置颜色
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
