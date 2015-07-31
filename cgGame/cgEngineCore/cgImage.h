
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
	// �������Ļ��ƺ���
	virtual void Draw(const cgRectF & kSrcRect,const cgRectF & kDestRect,
		cgColor color = 0xffffffff) = NULL;

	// ���û���֮һ���ѵ�ǰͼƬԭ�����Ƶ�ָ��λ�ã�����������
	void DrawToPoint(float x, float y, cgColor color = 0xffffffff);

	// ���û���֮�����ѵ�ǰͼƬ���Ƶ�ָ�����򣬿�������
	void DrawToRect(const cgRectF & kDestRect, cgColor color = 0xffffffff);

	// ���û���֮�����ٶ�
	void DrawToRect(float x, float y, float w, float h, cgColor color = 0xffffffff);

	// ���û���֮�����ѵ�ǰͼƬ��һ���֣�����ȫ����ԭ�����Ƶ�ָ��λ�ã�������
	void DrawPartToPoint(const cgRectF & kSrcRect, float x, float y, cgColor color = 0xffffffff);

	// ��ȡ��������
	virtual bool PointToFinalTextureCoordinate(float x, float y, float &u, float &v) = NULL;

	// ��ȡID
	virtual cgID GetTextureID() = NULL;

	virtual float GetWidth()const = NULL;
	virtual float GetHeight()const = NULL;

	void DrawEx(float centerX, float centerY,
		float w, float h,
		cgColor color, float rotation, 
		bool xFlip = false, bool yFlip = false);

public:
	// ���ļ�����ͼƬ
	static cgImagePtr LoadFromFile(LPCTSTR lpctPath);

	// ����һ���հ�ͼƬ
	static cgImagePtr CreateImage(int w, int h);

	// ����һ��ͼƬ�ü�
	static cgImagePtr ClipFromImage(cgImagePtr spImage, const cgRectF& rect);
};

#endif // CGImage_h__
