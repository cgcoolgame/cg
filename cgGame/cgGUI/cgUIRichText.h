//////////////////////////////////////////////////////////////////////////
// ���ı���ʵ��
// �ο�html��ǩ�������иĶ�
//////////////////////////////////////////////////////////////////////////
#ifndef cgUIRichText_h__
#define cgUIRichText_h__
#include "cgUIDef.h"
#include <cgRefObject.h>
#include <vector>
#include "cgUIRichChar.h"
#include "cgUIWidget.h"

typedef std::vector<cgUIRichCharPtr> RichCharPtrList;

class cgRichLine:public cgRefObject
{
public:
	cgRichLine()
	{
		xOff = 0;
		w = 0;
		h = 0;
	}
	int xOff;
	int yOff;
	int w;
	int h;
	RichCharPtrList kList;
};

typedef cgSmartPointer<cgRichLine> cgRichLinePtr;
typedef std::vector<cgRichLinePtr> RichLinePtrList;

class cgUIRichText:
	public cgUIWidget
{
public:
	cgUIRichText(void);
	cgUIRichText(const string & strName);

	virtual ~cgUIRichText(void);

	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);
protected:
	virtual void DrawText(const cgRectF& clipRect);

	cgUIRichCharPtr PickInteractiveChar(int x, int y);

	void ParseRawString();
	void ParseControlField(LPCTSTR str);
	int ParseFieldName(LPCTSTR str, LPTSTR szName);
	int EatSpace(LPCTSTR str);

	// ���һ�������ַ���
	void InsertNormalChar(LPCTSTR str);
	void InsertRichChar(cgUIRichChar * richChar);

	// ����������
	void MeasureRichText();

	bool OnLButtonDown( unsigned wparam, unsigned lparam );
	bool OnRButtonDown(unsigned wparam, unsigned lparam);
	bool OnMouseMove( unsigned wparam, unsigned lparam );

	// �ı����
	virtual void OnSizeChanged();
	virtual void OnTextChanged();
	virtual void OnFontChanged();
	virtual void OnTextStyleChanged();
	virtual void OnTextColorChanged();
	virtual void OnTextRowSpaceChanged();
protected:
	// ���ı��б�
	RichCharPtrList m_kCharList;
	RichLinePtrList m_kLineList;

	cgUIRichCharPtr m_spHotChar;
};

#endif // cgUIRichText_h__
