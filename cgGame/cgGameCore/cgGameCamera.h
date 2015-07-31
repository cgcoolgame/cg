
#ifndef cgGameCamera_h__
#define cgGameCamera_h__

#include "cgGameObject.h"
#include "cgCamera.h"
#include "cgSmartPointer.h"

class cgGameCamera;
typedef cgSmartPointer<cgGameCamera> cgGameCameraPtr;

class cgGameCamera:
	public cgGameObject,
	public cgCamera
{
public:
	cgGameCamera(void);
	cgGameCamera(const string & strName);
	~cgGameCamera(void);

	// 视口信息，都是世界坐标系的
	virtual cgVector GetViewCenter();
	virtual cgVector GetViewScale();

	// 视口与缩放的关系
	// 放大：景物放大，视口变小
	// 缩小：景物缩小，视口变大
	virtual cgSizeF GetViewSize();

	// 视口
	virtual cgRectF GetViewRect();

	// 判断一个物体是否可见
	virtual bool IsBoundInView(const cgRectF& bound);

	// 坐标转换
	virtual void ScreenToWorld(float & x, float & y);
	virtual void ScreenToWorld(cgVector& v);

	virtual void WorldToScreen(float & x, float & y);
	virtual void WorldToScreen(cgVector& v);
};
#endif // cgGameCamera_h__

