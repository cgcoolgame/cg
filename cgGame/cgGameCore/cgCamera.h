#ifndef cgCamera_h__
#define cgCamera_h__

#include "cgDefine.h"

class cgCamera
{
public:
	cgCamera(void);
	virtual ~cgCamera(void);

	// �ӿ���Ϣ��������������ϵ��
	virtual cgVector GetViewCenter() = NULL;

	// ����
	virtual cgVector GetViewScale() = NULL;

	// �ӿ������ŵĹ�ϵ
	// �Ŵ󣺾���Ŵ��ӿڱ�С
	// ��С��������С���ӿڱ��
	virtual cgSizeF GetViewSize() = NULL;

	// �ӿ�
	virtual cgRectF GetViewRect() = NULL;

	// �ж�һ�������Ƿ�ɼ�
	virtual bool IsBoundInView(const cgRectF& bound) = NULL;

	// ����ת��
	virtual void ScreenToWorld(float & x, float & y) = NULL;
	virtual void ScreenToWorld(cgVector& v) = NULL;

	virtual void WorldToScreen(float & x, float & y) = NULL;
	virtual void WorldToScreen(cgVector& v) = NULL;

	// ֻ������Ⱦ��ʱ������ã�����һ��ֻ����һ���������Ⱦ
	static cgCamera * GetRenderCamera();
	static cgCamera * SetRenderCamera(cgCamera * pkCamera);

private:
	static cgCamera * ms_pkCurCamera;
};
#endif // cgCamera_h__

