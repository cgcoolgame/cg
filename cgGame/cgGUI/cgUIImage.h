#ifndef cgUIImage_h__
#define cgUIImage_h__

#include "cgRefObject.h"
#include "cgSmartPointer.h"


class cgUIImage:public cgRefObject
{
public:

	// 用路径加载一个UImage
	cgUIImage(LPCTSTR srcPath);		

	// 用图片id来加载一个UIImage
	cgUIImage(cgID srcID);			

	virtual ~cgUIImage(void);

	// 图片的id标识
	cgID GetID();

	// 宽高
	int GetWidth();
	int GetHeight();

	// 绘制
	void Draw(const cgRectF & srcRect, const cgRectF & destRect);
	void DrawToRect(const cgRectF & destRect);
	void DrawToPoint(int x, int y);

private:
	cgID m_id;
	int m_nWidth;
	int m_nHeight;
};

typedef cgSmartPointer<cgUIImage> cgUIImagePtr;

#endif // cgUIImage_h__
