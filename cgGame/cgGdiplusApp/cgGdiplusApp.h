#ifndef cgGdiplusApp_h__
#define cgGdiplusApp_h__
#include "cgWinApp.h"

class cgGdiplusApp :
	public cgWinApp
{
public:
	cgGdiplusApp(void);
	~cgGdiplusApp(void);
public:
	virtual bool Initialize(int nWidth, int nHeight, 
		int nStyle = WS_POPUP|WS_SYSMENU, 
		int nStyleEx = WS_EX_LAYERED);

	virtual bool OnRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	// 留给继承
	virtual bool DoInitialize();
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// 下面的可以继承，但是一般不推荐
	virtual void OnIdle();
	virtual void Update(float fTime);
	void Render();
protected:

	// 是否加载完成
	bool m_bIsInitialized;
};

#endif // cgGdiplusApp_h__
