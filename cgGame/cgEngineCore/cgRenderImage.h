#ifndef cgRenderImage_h__
#define cgRenderImage_h__
#include "cgImage.h"

class cgRenderImage: public cgImage
{
public:

	// ������Դ·������һ��image
	cgRenderImage(LPCTSTR path);

	// ����ָ����С����һ��
	cgRenderImage(int w, int h);

	virtual ~cgRenderImage();
public:

	// ��ȡ������
	virtual cgID GetTextureID();

	// ��ȡ�����С
	virtual float GetWidth()const;
	virtual float GetHeight()const;

	// ����
	virtual void Draw(const cgRectF & srcRect,const cgRectF & destRect,
		cgColor color);

	// ��ȡ��������
	virtual bool PointToFinalTextureCoordinate(float x, float y, float &u, float &v) ;

protected:
	// ������
	cgID m_idTex;
	float m_fWidth;
	float m_fHeight;
};

typedef cgSmartPointer<cgRenderImage> cgRenderImagePtr;

#endif // cgTexturedImage_h__
