#ifndef cgUIWebPage_h__
#define cgUIWebPage_h__

// 这是一个网页显示器，暂时只支持windows api，以后可能会扩展吧
// 通过创建一个主窗口的子窗口来实现显示网页的，不是严格意义上的逻辑UI

// 注意：这个是通过离屏绘制来显示到屏幕的，所以效率可能略差，
// 缺点还有就是除了点击链接，其他的操作都很迟钝、吃力，输入框的
// 光标看不到闪烁，等等各种缺点
// 但是它的“逻辑UI”表现最好，其他窗口可以覆盖它。
// 友情提示：如果不是特别需要，尽量使用cgUIWebPageEx来完成网页显示吧

#include "cgUIWidget.h"
#include <atlbase.h>
#include <atlwin.h>
#include <exdisp.h>

class cgUISurface;

class cgUIWebPage :
	public cgUIWidget
{
public:
	cgUIWebPage(void);
	~cgUIWebPage(void);

public:
	// 初始化
	bool Initialize(cgHwnd hMainWnd, int x, int y, int w, int h);

	// 导航到某个网页
	bool Navigate(LPCTSTR url, bool bForceRefresh = false);

	bool Refresh();

	// 由于不是逻辑UI，所以当位置和大小改变的时候，需要
	//	调整web窗体的位置和大小
	virtual void SetSize(int w, int h);
	virtual void Move(int x, int y);

	// 设置主动更新的时间间隔
	void SetFreshTimeSpace(float fTimeSpace);
	float GetFreshTimeSpace();

protected:

	// 更新
	virtual void Update(float fTime);

	// 绘制
	virtual void DrawBackPic(const cgRectF& clipRect);

private:

	// 调整网页，以适应新的大小、位置
	void AdjustWebRect();

private:
	CAxWindow m_kContainer;
	IWebBrowser2 * m_pkBrower;

	float m_fLastUpdateTime;
	float m_fFreshTimeSpace;// 主动更新的时间间隔

	cgUISurface * m_pkRenderSurface;
};

#endif // cgUIWebPage_h__
