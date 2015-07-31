
#ifndef CGImage_h__
#define CGImage_h__

#include "cgRefObject.h"
#include "cgSmartPointer.h"

class cgImage;
typedef cgSmartPointer<cgImage> cgImagePtr;

class cgImage:public cgRefObject
{
public:
	cgImage();
	virtual ~cgImage(void);
public:
	// 最完整的绘制函数
	virtual void Draw(const cgRectF & kSrcRect,const cgRectF & kDestRect,
		cgColor color = 0xffffffff) = NULL;

	// 常用绘制之一：把当前图片原样绘制到指定位置，不考虑缩放
	void DrawToPoint(float x, float y, cgColor color = 0xffffffff);

	// 常用绘制之二：把当前图片绘制到指定区域，考虑缩放
	void DrawToRect(const cgRectF & kDestRect, cgColor color = 0xffffffff);

	// 常用绘制之二，再二
	void DrawToRect(float x, float y, float w, float h, cgColor color = 0xffffffff);

	// 常用绘制之三：把当前图片的一部分（包含全部）原样绘制到指定位置，不缩放
	void DrawPartToPoint(const cgRectF & kSrcRect, float x, float y, cgColor color = 0xffffffff);

	// 获取纹理坐标
	virtual bool PointToFinalTextureCoordinate(float x, float y, float &u, float &v) = NULL;

	// 获取ID
	virtual cgID GetTextureID() = NULL;

	virtual float GetWidth()const = NULL;
	virtual float GetHeight()const = NULL;

	void DrawEx(float centerX, float centerY,
		float w, float h,
		cgColor color, float rotation, 
		bool xFlip = false, bool yFlip = false);

public:
	// 从文件加载图片
	static cgImagePtr LoadFromFile(LPCTSTR lpctPath);

	// 创建一个空白图片
	static cgImagePtr CreateImage(int w, int h);

	// 从另一个图片裁剪
	static cgImagePtr ClipFromImage(cgImagePtr spImage, const cgRectF& rect);
};

#endif // CGImage_h__
