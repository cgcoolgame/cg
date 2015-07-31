#ifndef cgRefImage_h__
#define cgRefImage_h__
#include "cgImage.h"

// 引用图片，自身不是一个独立的图片，而是共享别的图片的一部分
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

	// 获取ID
	virtual cgID GetTextureID();

private:
	cgRectF m_kClipRect;

	cgImagePtr m_spParentImage;
};

#endif // cgRefImage_h__
