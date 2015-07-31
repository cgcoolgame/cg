
#ifndef cgGameLayer_h__
#define cgGameLayer_h__

#include "cggameobject.h"
#include "cgGameCamera.h"

class cgGameLayer :
	public cgGameObject
{
public:
	cgGameLayer(void);
	cgGameLayer(const string &strName);

	~cgGameLayer(void);

	virtual void Render();
	virtual cgGameObject * Pick(float pointX, float pointY, bool bScreenPoint);
	
	cgGameCamera * GetCamera();
protected:
	cgGameCamera* m_pkCamera;
};

typedef cgSmartPointer<cgGameLayer> cgGameLayerPtr;
#endif // cgGameLayer_h__
