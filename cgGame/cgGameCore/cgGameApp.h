//////////////////////////////////////////////////////////////////////////
//	FileName:		CGGameApp.h
//	Author:			Master
//	Date:			2014.4.15
//	Desc:			һ������ģ�����Ϸ������ܣ����ڿ�����Ϸģ�ͽ���
//	Desc:			��Ȼ���ⲻ��Ψһ��ѡ��
//////////////////////////////////////////////////////////////////////////
#ifndef CGGameApp_h__
#define CGGameApp_h__

#include "cgWinApp.h"
#include "cgGameMessage.h"
#include "cgGameCommand.h"
#include "cgGameTask.h"
#include <list>

#define DEFAULT_GAME_MAX_FPS 60

class cgGameMessageListener;

class cgGameApp:
	public cgWinApp
{
public:
	cgGameApp();
	~cgGameApp(void);

public:
	// ��ʼ�������Ҵ���һ��ָ����С�Ĵ���
	virtual bool Initialize(int nWidth, int nHeight, 
		int nStyle = WS_OVERLAPPEDWINDOW, 
		int nStyleEx = WS_EX_APPWINDOW );

	// ��Ϣ������
	virtual bool OnRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// ��ȡ��ϷAppʵ��
	static cgGameApp * GetGameApp();
public:

	// ��һ֡�Ŀ�ʼʱ��
	float GetLastFrameBeginTime();

	// ��ǰ֡�Ŀ�ʼʱ��
	float GetFrameBeginTime();

	// ��֮֡��Ĳ�ֵ��Ҳ������һ֡�ĳ���ʱ��
	float GetDeltaTime();

	// FPS���
	void SetMaxFPS(int nFPS);
	int GetMaxFPS();
	int GetCurFPS();
	void ShowFPS(bool bShow);
	bool IsShowFPS();

	// ʱ����٣����Կ��Ƽ��١����١�����ʱ�䶳��
	void SetTimeScale(float fAccelerate);
	float GetTimeScale();

protected:

	virtual bool DoInitGame();
	// ʵ�ʴ�����Ϣ
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// ���ڳߴ緢���仯
	virtual bool OnSizeChanged();

	// �̳���cgApp������ʱ��Ƭ
	virtual void OnIdle();

	// ����
	virtual void Update(float fDeltaTime);
	// ������Ϸ�߼�
	virtual void DoUpdateGame(float fDeltaTime);

	// ��Ⱦ��أ���ա���������ʾ
	void Render();
	// ������Ⱦ������̳У���һЩ�������
	virtual void DoRenderGame();

	// FPS���
	void LockFPS();
	void DrawFPS();

protected:

	// ��һ֡�Ŀ�ʼʱ��
	float m_fLastFrameBeginTime;

	// ��ǰ֡�Ŀ�ʼʱ��
	float m_fFrameBeginTime;

	// ��ǰ֡����һ֡��ʱ���ֵ
	float m_fFrameDeltaTime;

	// ʱ����ٱ���
	float m_fTimeScale; // ʱ�䱶��

	// ���֡��
	int m_nMaxFPS;
	// ��ǰ֡��
	int m_nCurFPS;
	// �Ƿ���ʾ֡��
	bool m_bShowFPS;
	
	// �Ƿ�������
	bool m_bIsInitialized;
};

#endif // CGGameApp_h__
