
#ifndef cgUIButton_h__
#define cgUIButton_h__

#include "cgUIWidget.h"

class cgUIButton :
	public cgUIWidget
{
public:
	cgUIButton(void);
	cgUIButton(const string & strName);

	~cgUIButton(void);

	// …Ë÷√∞¥≈•Õº∆¨
	void SetButtonPic(LPCTSTR lpctNormal, LPCTSTR lpctHot, 
		LPCTSTR lpctPress, LPCTSTR lpctDisable);

	void SetButtonPic(cgID idNormal, cgID idHot, 
		cgID idPress, cgID idDisable);

	void SetButtonPic(cgUIImagePtr spNormal, cgUIImagePtr spHot,
		cgUIImagePtr spPress, cgUIImagePtr spDisable);

	void SetButtonColor(cgColor uNormalColor,
		cgColor uHotColor,
		cgColor uPressColor,
		cgColor uDisableColor);
protected:
	void SetupParams();

	virtual void DrawBackPic(const cgRectF& clipRect);
	virtual void DrawBackground(const cgRectF& clipRect);

protected:
	cgUIImagePtr m_spNormalPic;
	cgUIImagePtr m_spHotPic;
	cgUIImagePtr m_spPressPic;
	cgUIImagePtr m_spDisablePic;

	cgColor m_uHotColor;
	cgColor m_uPressColor;
	cgColor m_uDisableColor;
};

#endif // cgUIButton_h__
