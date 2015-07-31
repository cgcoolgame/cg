#ifndef cgUIImage_h__
#define cgUIImage_h__

#include "cgRefObject.h"
#include "cgSmartPointer.h"


class cgUIImage:public cgRefObject
{
public:

	// ��·������һ��UImage
	cgUIImage(LPCTSTR srcPath);		

	// ��ͼƬid������һ��UIImage
	cgUIImage(cgID srcID);			

	virtual ~cgUIImage(void);

	// ͼƬ��id��ʶ
	cgID GetID();

	// ���
	int GetWidth();
	int GetHeight();

	// ����
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
