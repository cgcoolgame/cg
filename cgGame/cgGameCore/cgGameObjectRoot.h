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

	// ��ʼ��
	bool Initialize();

	// ����������Ϸ
	void Update(float deltaTime);
	void Render();
	bool OnRawMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	// ��չ��Σ�
	cgGameLayerPtr CreateLayer(const string & strLayer, float depth);
	cgGameLayerPtr GetLayer(const string & strLayer);

};

#endif // cgGameObjectRoot_h__
