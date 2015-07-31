#ifndef cgRenderImage_h__
#define cgRenderImage_h__
#include "cgImage.h"

class cgRenderImage: public cgImage
{
public:

	// 根据资源路径加载一个image
	cgRenderImage(LPCTSTR path);

	// 根据指定大小创建一个
	cgRenderImage(int w, int h);

	virtual ~cgRenderImage();
public:

	// 获取纹理句柄
	virtual cgID GetTextureID();

	// 获取纹理大小
	virtual float GetWidth()const;
	virtual float GetHeight()const;

	// 绘制
	virtual void Draw(const cgRectF & srcRect,const cgRectF & destRect,
		cgColor color);

	// 获取纹理坐标
	virtual bool PointToFinalTextureCoordinate(float x, float y, float &u, float &v) ;

protected:
	// 纹理句柄
	cgID m_idTex;
	float m_fWidth;
	float m_fHeight;
};

typedef cgSmartPointer<cgRenderImage> cgRenderImagePtr;

#endif // cgTexturedImage_h__
