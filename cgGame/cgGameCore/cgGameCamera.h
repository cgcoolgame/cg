
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

	// �ӿ���Ϣ��������������ϵ��
	virtual cgVector GetViewCenter();
	virtual cgVector GetViewScale();

	// �ӿ������ŵĹ�ϵ
	// �Ŵ󣺾���Ŵ��ӿڱ�С
	// ��С��������С���ӿڱ��
	virtual cgSizeF GetViewSize();

	// �ӿ�
	virtual cgRectF GetViewRect();

	// �ж�һ�������Ƿ�ɼ�
	virtual bool IsBoundInView(const cgRectF& bound);

	// ����ת��
	virtual void ScreenToWorld(float & x, float & y);
	virtual void ScreenToWorld(cgVector& v);

	virtual void WorldToScreen(float & x, float & y);
	virtual void WorldToScreen(cgVector& v);
};
#endif // cgGameCamera_h__

