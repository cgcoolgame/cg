#ifndef cgRefImage_h__
#define cgRefImage_h__
#include "cgImage.h"

// ����ͼƬ��������һ��������ͼƬ�����ǹ�����ͼƬ��һ����
class cgRefImage:public cgImage
{
public:
	cgRefImage(const cgImagePtr &spParent, const cgRectF &kClipRect);
	~cgRefImage();
public:
	virtual void Draw(const cgRectF & kSrcRect,const cgRectF & kDestRect,
		cgColor color = 0xffffffff);

	virtual float GetWidth()const;
	virtual float GetHeight()const;

	virtual bool PointToFinalTextureCoordinate(float x, float y, float &u, float &v) ;

	// ��ȡID
	virtual cgID GetTextureID();

private:
	cgRectF m_kClipRect;

	cgImagePtr m_spParentImage;
};

#endif // cgRefImage_h__
