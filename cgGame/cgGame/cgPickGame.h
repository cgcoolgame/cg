
#ifndef cgPickGame_h__
#define cgPickGame_h__

static const float PickGameInitRefreshTimeSpace = 1.0f/**0.01f*/;
static const float PickGameObjectLifeTime = 1.5f;
static const float PickGameObjectMoveSpeed = 100.0f;
static const int PickGame_Lose_Count = 10;


#include "cggameapp.h"
#include <cgGameObject.h>
#include <cgGameCamera.h>
#include <cgUIEventListener.h>
#include "cgUIObject.h"

class cgPickGame :
	public cgGameApp,
	public cgSingleton<cgPickGame>,
	public cgUIEventListenerSample
{
public:
	enum GameState
	{
		eStart = 0,
		eMenu = 1,
		eRun = 2,
		eEndMenu = 3,
		eRestart = 4,
	};

public:
	cgPickGame(void);
	~cgPickGame(void);

	virtual int OnMouseDown(cgUIObject* eventSrc);

protected:

	virtual bool DoInitGame();
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoUpdateGame(float fDeltaTime);
	virtual void DoRenderGame();

private:
	void InitUI();

	void StartGame();
	void StopGame();
	void Restart();

	void UpdatePickGame(float fDeltaTime);

	void CheckPick(float x, float y);
	void CheckEscape();
	void CheckRefreshNew();
	void CheckDirection();

	void OnPickTotalChanged();

	void DrawScore();
protected:
	float m_fCurRefreshTimeSpace;
	float m_fTime;

	float m_fCurMoveSpeed;

	int m_nLevel;
	int m_nPickTotal;
	int m_nTotal;
	int m_nEscapeTotal;

	GameState m_eState;

	cgGameObjectPtr m_spPickGameRoot;
	cgGameCameraPtr m_spCamera;

	cgUIObjectPtr m_spGameOver;
};

#endif // cgPickGame_h__
