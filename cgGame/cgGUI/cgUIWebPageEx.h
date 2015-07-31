//////////////////////////////////////////////////////////////////////////
// 创建一个从属窗口（注意，是从属窗口，不是子窗口），把网页进去
// 用两个平行窗体来实现，效果最好，但是有一个缺点：
// 缺点：不支持透明，必须是顶层窗口，其他逻辑UI无法覆盖之。
// 由于不支持透明，所以它的子窗口基本都被它挡住了，所以对于它还是不要添加子窗口的好
// 除此之外，堪称完美
//////////////////////////////////////////////////////////////////////////

#ifndef cgUIWebPageEx_h__
#define cgUIWebPageEx_h__

#include <atlbase.h>
#include <atlwin.h>
#include <exdisp.h>

#include "cgUIWidget.h"


class cgUIWebPageEx :
	public cgUIWidget
{
public:
	cgUIWebPageEx(void);
	~cgUIWebPageEx(void);

public:
	// 初始化
	bool Initialize(cgHwnd hMainWnd, int x, int y, int w, int h);

	// 设置虚拟控件和webpage的偏移，默认web是充满整个控件的
	void SetWebpageOffset(int leftOffset, int rightOffset, int topOffset, int bottomOffset);

	// 导航到某个网页
	bool Navigate(LPCTSTR url, bool bForceRefresh = false);
	const cgString& GetCurUrl();

	// 刷新网页
	bool Refresh();

	// 由于不是逻辑UI，所以当位置和大小改变的时候，需要
	//	调整web窗体的位置和大小
	virtual void SetVisible(bool bVisible);

	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

protected:
	virtual void OnPositionChanged();
	virtual void OnSizeChanged();
private:

	// 调整网页，以适应新的大小、位置
	void AdjustWebRect();

private:
	CAxWindow m_kContainer;
	IWebBrowser2 * m_pkBrower;

	cgString m_strUrl;
	int m_nLeftOffset;
	int m_nRightOffset;
	int m_nTopOffset;
	int m_nBottomOffset;
};

#endif // cgUIWebPageEx_h__
