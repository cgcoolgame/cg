#ifndef cgSceneManager_h__
#define cgSceneManager_h__

#include "cgSingleton.h"
#include "cgGameLayer.h"

class cgSceneManager:
	public cgSingleton<cgSceneManager>
{
public:
	cgSceneManager(void);
	~cgSceneManager(void);

	bool Initialize();
	
	void Update(float deltaTime);
	bool OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);

// ------------------------------------------------------------------
	cgGameLayerPtr GetSceneRoot();
	cgGameCameraPtr GetSceneCamera();

	void ScreenToScene(cgVector& v);
	void SceneToScreen(cgVector& v);

protected:
	cgGameLayerPtr m_spSceneRoot;
	cgGameCameraPtr m_spSceneCamera;
};


#endif // cgSceneManager_h__
