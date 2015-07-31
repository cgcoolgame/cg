#ifndef cgGameObjectRoot_h__
#define cgGameObjectRoot_h__

#include <cgSingleton.h>
#include "cgGameLayer.h"

class cgGameObjectRoot:
	public cgSingleton<cgGameObjectRoot>
{
public:
	cgGameObjectRoot(void);
	~cgGameObjectRoot(void);

	// 初始化
	bool Initialize();

	// 更新整个游戏
	void Update(float deltaTime);
	void Render();
	bool OnRawMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	// 扩展层次：
	cgGameLayerPtr CreateLayer(const string & strLayer, float depth);
	cgGameLayerPtr GetLayer(const string & strLayer);

};

#endif // cgGameObjectRoot_h__
