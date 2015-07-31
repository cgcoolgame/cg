//////////////////////////////////////////////////////////////////////////
// 富文本的实现
// 参考html标签，但是有改动
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

	// 添加一个正常字符串
	void InsertNormalChar(LPCTSTR str);
	void InsertRichChar(cgUIRichChar * richChar);

	// 测量、排列
	void MeasureRichText();

	bool OnLButtonDown( unsigned wparam, unsigned lparam );
	bool OnRButtonDown(unsigned wparam, unsigned lparam);
	bool OnMouseMove( unsigned wparam, unsigned lparam );

	// 文本相关
	virtual void OnSizeChanged();
	virtual void OnTextChanged();
	virtual void OnFontChanged();
	virtual void OnTextStyleChanged();
	virtual void OnTextColorChanged();
	virtual void OnTextRowSpaceChanged();
protected:
	// 富文本列表
	RichCharPtrList m_kCharList;
	RichLinePtrList m_kLineList;

	cgUIRichCharPtr m_spHotChar;
};

#endif // cgUIRichText_h__
