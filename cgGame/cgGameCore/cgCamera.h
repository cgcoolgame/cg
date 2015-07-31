#ifndef cgCamera_h__
#define cgCamera_h__

#include "cgDefine.h"

class cgCamera
{
public:
	cgCamera(void);
	virtual ~cgCamera(void);

	// 视口信息，都是世界坐标系的
	virtual cgVector GetViewCenter() = NULL;

	// 缩放
	virtual cgVector GetViewScale() = NULL;

	// 视口与缩放的关系
	// 放大：景物放大，视口变小
	// 缩小：景物缩小，视口变大
	virtual cgSizeF GetViewSize() = NULL;

	// 视口
	virtual cgRectF GetViewRect() = NULL;

	// 判断一个物体是否可见
	virtual bool IsBoundInView(const cgRectF& bound) = NULL;

	// 坐标转换
	virtual void ScreenToWorld(float & x, float & y) = NULL;
	virtual void ScreenToWorld(cgVector& v) = NULL;

	virtual void WorldToScreen(float & x, float & y) = NULL;
	virtual void WorldToScreen(cgVector& v) = NULL;

	// 只有在渲染的时候可以用，而且一次只能有一个相机在渲染
	static cgCamera * GetRenderCamera();
	static cgCamera * SetRenderCamera(cgCamera * pkCamera);

private:
	static cgCamera * ms_pkCurCamera;
};
#endif // cgCamera_h__

