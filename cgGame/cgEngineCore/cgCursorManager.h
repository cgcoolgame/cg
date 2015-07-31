////////////////////////////////////////////////////////////////////
// 实验性质的光标管理器
// 可以把光标的主键改成id，
// 读取方式改成走配置
// todo
// 纯windows用，反正也跨不了平台了
// master [5/3/2015 Administrator]
////////////////////////////////////////////////////////////////////
#ifndef cgCursorManager_h__
#define cgCursorManager_h__
#include "cgSingleton.h"
#include <map>

typedef std::map<string, HCURSOR> cgCursorMap;

class cgCursorManager:
	public cgSingleton<cgCursorManager>
{
public:
	cgCursorManager(void);
	~cgCursorManager(void);

	bool Initialize();
	bool OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

	void SetDefaultCursor(const string & cursor);
	void SetCursor(const string& cursor);
	void Reset();

	void ShowCursor(bool bShow);
	bool IsCursorShow();

protected:
	void LoadCursor();

	HCURSOR GetCursor(const string& cursor);

protected:

	cgCursorMap m_kCursorMap;
	HCURSOR m_hCurCursor;
	HCURSOR m_hDefaultCursor;
	bool m_bShowCursor;
};

#endif // cgCursorManager_h__
