
#ifndef cgGameSpirit_h__
#define cgGameSpirit_h__
#include "cggameobject.h"
#include "cgImage.h"

class cgGameSprite :
	public cgGameObject
{
public:
	cgGameSprite(void);
	cgGameSprite(const string& strName);
	cgGameSprite(const cgString& strPath);
	cgGameSprite(cgImagePtr spImage);

	void SetImage(const cgString& strPath);
	void SetImage(cgImagePtr spImage);

protected:
	virtual void DoRenderSelf(cgCamera * renderCamera);

protected:
	cgImagePtr m_spImage;
};
typedef cgSmartPointer<cgGameSprite> cgGameSpiritPtr;

#endif // cgGameSpirit_h__
