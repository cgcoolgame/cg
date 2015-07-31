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
	// �����̳�
	virtual bool DoInitialize();
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// ����Ŀ��Լ̳У�����һ�㲻�Ƽ�
	virtual void OnIdle();
	virtual void Update(float fTime);
	void Render();
protected:

	// �Ƿ�������
	bool m_bIsInitialized;
};

#endif // cgGdiplusApp_h__
