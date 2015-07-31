////////////////////////////////////////////////////////////////////
// ʵ�����ʵĹ�������
// ���԰ѹ��������ĳ�id��
// ��ȡ��ʽ�ĳ�������
// todo
// ��windows�ã�����Ҳ�粻��ƽ̨��
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
