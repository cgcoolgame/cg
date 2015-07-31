#ifndef cgGameUIManager_h__
#define cgGameUIManager_h__

#include "cgsingleton.h"
#include "cgGameCamera.h"
#include "cgGameLayer.h"


class cgGameUIManager :
	public cgSingleton<cgGameUIManager>
{
public:
	cgGameUIManager(void);
	~cgGameUIManager(void);

	bool Initialize();

	void Update(float deltaTime);
	bool OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);
// ------------------------------------------------------------------

	cgGameLayerPtr GetUIRoot();
	cgGameCameraPtr GetUICamera();

	void ScreenToUI(cgVector& v);
	void UIToScreen(cgVector& v);

protected:
	cgGameLayerPtr m_spUIRoot;
	cgGameCameraPtr m_spUICamera;

	cgGameObjectPtr m_spFocus;
	cgGameObjectPtr m_spPick;
};

#endif // cgGameUIManager_h__
