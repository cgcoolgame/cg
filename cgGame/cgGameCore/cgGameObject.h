
#ifndef cgGameObject_h__
#define cgGameObject_h__

#include "cgrefobject.h"
#include "cgGameObjectDef.h"
#include <vector>
#include "cgSmartPointer.h"
#include "cgAction.h"
#include "cgCamera.h"

#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif

class cgGameObject ;
typedef cgSmartPointer<cgGameObject> cgGameObjectPtr;
typedef std::vector<cgGameObjectPtr> cgGameObjectPtrList;

class cgGameObject :
	public cgRefObject
{
public:
	cgGameObject(void);
	cgGameObject(const string & strName);
	~cgGameObject(void);

public:
	static cgGameObjectPtr Root();
	static void ClearAll();
	static cgGameObject * FindObject(const string & strName);
public:
// ----------------------------------------------------------
	// ��ܽӿ�
	virtual void Update(float deltaTime);
	virtual void Render();

	// ��Ļ���꣬ʰȡ
	virtual cgGameObject* Pick(float pointX, float pointY, bool bScreenPoint);
// ----------------------------------------------------------
	// ����
	void SetName(const string & name);
	const string & GetName()const;

	// ���
	void SetLayer(const string & layer);
	const string& GetLayer();

	// ����ת���ɿɴ�ӡ���ַ���
	virtual string ToString();
// ----------------------------------------------------------

	// ��ȡ�ýڵ��Ѿ���Ծ�˶����
	float GetActiveTime()const;

// ----------------------------------------------------------
	// ��ȣ����ڻ���˳��
	void SetDepth(cgGameObjectDepth depth);
	cgGameObjectDepth GetDepth()const;

	// ֪ͨ�ýڵ㣬�ӽڵ������б仯����Ҫ�ں��ʵ�ʱ�������ˡ�
	void SetDepthDirty();
	bool IsDepthDirty()const;
// ----------------------------------------------------------

	// ���ӽڵ����
	cgGameObject * GetParent();
	cgGameObject * AttachChild(cgGameObject * pkChild);
	cgGameObjectPtr DetachChild(cgGameObject * pkChild);
	void DetachAllChild();

	// �ӽڵ�����
	size_t GetChildCount();
	cgGameObject * GetChild(size_t index);

	// ֻ�����ӽڵ�
	cgGameObject * FindChild(const string & strName);

	// �ݹ��������еĽڵ㣬��������
	cgGameObject * FindRecursive(const string & strName);
// ----------------------------------------------------------

	// �任����
	const cgTransform& GetWorldTransform()const;
	const cgTransform& GetLocalTransform()const;

	// ����λ��
	void SetWorldPosition(const cgVector& pos);
	void SetWorldPosition(float x, float y);
	const cgVector& GetWorldPosition()const;

	// ����ڸ��ڵ��λ��
	void SetLocalPosition(const cgVector& pos);
	void SetLocalPosition(float x, float y);
	const cgVector& GetLocalPosition()const;

	// �����ƶ�
	void Move(const cgVector & v);
	void Move(float deltaX, float deltaY);

	// ��������
	void SetWorldScale(const cgVector& scale);
	void SetWorldScale(float scaleX, float scaleY);
	const cgVector& GetWorldScale()const;

	// ����ڸ��ڵ������
	void SetLocalScale(const cgVector & scale);
	void SetLocalScale(float scaleX, float scaleY);
	const cgVector& GetLocalScale();

	// �������ţ��ۼ�ʽ����
	void LocalScale(const cgVector & scale);
	void LocalScale(float scaleX, float scaleY);

	// ��������
	void WorldScale(const cgVector & scale);
	void WorldScale(float scaleX, float scaleY);

	// ������ת
	void SetWorldRotation(float rotation);
	float GetWorldRotation()const;

	// ����ڸ��ڵ����ת
	void SetLocalRotation(float rotation);
	float GetLocalRotation();

	// ������ת
	void Rotate(float rotation);

	// ����ĳ������ת
	void RotateAround(float rotation, const cgVector& centerV);
	void RotateAround(float rotation, float centerX, float centerY);

// ----------------------------------------------------------
	// �ߴ�
	void SetSize(const cgSizeF & size);
	void SetSize(float w, float h);
	const cgSizeF& GetSize();

	// ��ȡ��Χ��
	virtual const cgRectF& GetBound(cgRectF& rect)const;
// ----------------------------------------------------------
	// ��������
	const cgRenderProps & GetRenderProperty();

	// ���Ƶ���ɫ��Ĭ���ǰ�ɫ
	void SetColor(cgColor color);
	cgColor GetColor();

	// ͸����
	void SetAlpha(float alpha);
	float GetAlpha();

	// ���������ɫ
	cgColor GetRenderColor();

	// ͸���ȱ仯
	void Alpha(float deltaAlpha);
// ----------------------------------------------------------

	// �Ƿ�������򲻻��ƣ������£�
	bool IsActive();
	void SetActive(bool bActive);

	// �Ƿ����ʰȡ
	bool IsPickable();
	void SetPickable(bool bPickable);

	bool IsVisible();
	void SetVisible(bool bVisible);

	void Destroy();
	bool IsDestroyed();

	// �Ƿ���Խ����¼�
	void SetEventable(bool eventable);
	bool IsEventable();

// ----------------------------------------------------------

	// gameobject��Ϊ
	cgAction* StartAction(cgAction * pkAction);
	cgAction* FindAction(const string& strName);

	size_t GetActionCount();
	void StopAction(const string & strName);
	void StopAllActions();
// ----------------------------------------------------------
	// ��ö�����һ���¼������¼��������ԡ����ӽڵ㴫��
	bool SendEvent(cgGameObjectEvent eventType, int firstParam, int secondParam);

protected:
	// ���������������Ϊ�˸����������õ�
	virtual void UpdateSelf(float deltaTime);
	virtual void DoUpdateSelf(float deltaTime);

	// �������е��ӽڵ�
	void UpdateChildren(float deltaTime);

	// ���ӽڵ�����
	void SortChildrenByDepth();

	// �������е���Ϊ
	void UpdateActions(float deltaTime);

	// ��Ⱦ
	virtual void RenderSelf();
	virtual void DoRenderSelf(cgCamera * renderCamera);

	// �����ӽڵ�
	void RenderChildren();

	// ʰȡ���ԣ�ֻ��λ�á���Χ��Ϣ���ж�
	bool PickHint(float pointX, float pointY, bool bScreenPoint);

	// �͸��ڵ�Ӵ���
	void DetachParent();
	void SetParent(cgGameObject * pkParent);
// ----------------------------------------------------------

	// �����ڵ��λ�ã�����λ�ã��仯ʱ
	void OnParentPositionChanged(const cgVector& v);

	// ����scale�����仯
	void OnScaleChanged(const cgVector& v);

	// �����ڵ�����ţ��������ţ��仯ʱ
	void OnParentScaleChanged(const cgVector& v);

	// �����ڵ����ת��������ת��ʱ���ӽڵ�Ҫ������Ӧ�ĸı�
	void OnParentRotationChanged(float rotation);

	// ���ߴ緢���仯ʱ
	virtual void OnSizeChanged();
// ----------------------------------------------------------

	// ���ӽڵ�����б�
	void AddChildToList(cgGameObject * pkChild);
	
	// �¼���أ���������
	virtual bool DoProcessEvent(cgGameObjectEvent eventType, int firstParam, int secondParam);

protected:
	string m_strName;
	string m_strLayer;
	
	// ��Ծ����ʱ��
	float m_fActiveTime;
	// ���
	cgGameObjectDepth m_fDepth;
	bool m_bIsDepthDirty; // �ӽڵ������б仯��Ҫ����

	// active��visible������
	// ��active��object�����ƣ������£�����Ӧ
	// ��visible��object�����ƣ��ɸ��£�����Ӧ
	bool m_bIsActive;
	bool m_bIsVisible;
	bool m_bIsPickable;
	bool m_bIsDestroyed;	// �Ƿ񱻱��Ϊ������
	bool m_bIsEventable;	// �ɷ�����¼�
	
	// �ߴ�
	cgSizeF m_kSize;

	// �任
	cgTransform m_kWorldTransform;
	cgTransform m_kLocalTransform;

	cgRenderProps m_kRenderProp;

	cgGameObject * m_pkParent;
	cgGameObjectPtrList m_kChildren;
	
	cgActionPtrList m_kActionList;
private:
	static cgGameObjectPtr ms_spRoot;
};

#endif // cgGameObject_h__
