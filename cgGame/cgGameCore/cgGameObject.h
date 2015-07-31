
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
	// 框架接口
	virtual void Update(float deltaTime);
	virtual void Render();

	// 屏幕坐标，拾取
	virtual cgGameObject* Pick(float pointX, float pointY, bool bScreenPoint);
// ----------------------------------------------------------
	// 名字
	void SetName(const string & name);
	const string & GetName()const;

	// 层次
	void SetLayer(const string & layer);
	const string& GetLayer();

	// 对象转化成可打印的字符串
	virtual string ToString();
// ----------------------------------------------------------

	// 获取该节点已经活跃了多久了
	float GetActiveTime()const;

// ----------------------------------------------------------
	// 深度，用于绘制顺序
	void SetDepth(cgGameObjectDepth depth);
	cgGameObjectDepth GetDepth()const;

	// 通知该节点，子节点的深度有变化，需要在合适的时候排序了。
	void SetDepthDirty();
	bool IsDepthDirty()const;
// ----------------------------------------------------------

	// 父子节点操作
	cgGameObject * GetParent();
	cgGameObject * AttachChild(cgGameObject * pkChild);
	cgGameObjectPtr DetachChild(cgGameObject * pkChild);
	void DetachAllChild();

	// 子节点数量
	size_t GetChildCount();
	cgGameObject * GetChild(size_t index);

	// 只搜索子节点
	cgGameObject * FindChild(const string & strName);

	// 递归搜索所有的节点，包括自身
	cgGameObject * FindRecursive(const string & strName);
// ----------------------------------------------------------

	// 变换操作
	const cgTransform& GetWorldTransform()const;
	const cgTransform& GetLocalTransform()const;

	// 世界位置
	void SetWorldPosition(const cgVector& pos);
	void SetWorldPosition(float x, float y);
	const cgVector& GetWorldPosition()const;

	// 相对于父节点的位置
	void SetLocalPosition(const cgVector& pos);
	void SetLocalPosition(float x, float y);
	const cgVector& GetLocalPosition()const;

	// 自身移动
	void Move(const cgVector & v);
	void Move(float deltaX, float deltaY);

	// 世界缩放
	void SetWorldScale(const cgVector& scale);
	void SetWorldScale(float scaleX, float scaleY);
	const cgVector& GetWorldScale()const;

	// 相对于父节点的缩放
	void SetLocalScale(const cgVector & scale);
	void SetLocalScale(float scaleX, float scaleY);
	const cgVector& GetLocalScale();

	// 自身缩放，累加式缩放
	void LocalScale(const cgVector & scale);
	void LocalScale(float scaleX, float scaleY);

	// 自身缩放
	void WorldScale(const cgVector & scale);
	void WorldScale(float scaleX, float scaleY);

	// 世界旋转
	void SetWorldRotation(float rotation);
	float GetWorldRotation()const;

	// 相对于父节点的旋转
	void SetLocalRotation(float rotation);
	float GetLocalRotation();

	// 自身旋转
	void Rotate(float rotation);

	// 绕着某个点旋转
	void RotateAround(float rotation, const cgVector& centerV);
	void RotateAround(float rotation, float centerX, float centerY);

// ----------------------------------------------------------
	// 尺寸
	void SetSize(const cgSizeF & size);
	void SetSize(float w, float h);
	const cgSizeF& GetSize();

	// 获取包围盒
	virtual const cgRectF& GetBound(cgRectF& rect)const;
// ----------------------------------------------------------
	// 绘制属性
	const cgRenderProps & GetRenderProperty();

	// 绘制的颜色，默认是白色
	void SetColor(cgColor color);
	cgColor GetColor();

	// 透明度
	void SetAlpha(float alpha);
	float GetAlpha();

	// 计算绘制颜色
	cgColor GetRenderColor();

	// 透明度变化
	void Alpha(float deltaAlpha);
// ----------------------------------------------------------

	// 是否活动（不活动则不绘制，不更新）
	bool IsActive();
	void SetActive(bool bActive);

	// 是否可以拾取
	bool IsPickable();
	void SetPickable(bool bPickable);

	bool IsVisible();
	void SetVisible(bool bVisible);

	void Destroy();
	bool IsDestroyed();

	// 是否可以接受事件
	void SetEventable(bool eventable);
	bool IsEventable();

// ----------------------------------------------------------

	// gameobject行为
	cgAction* StartAction(cgAction * pkAction);
	cgAction* FindAction(const string& strName);

	size_t GetActionCount();
	void StopAction(const string & strName);
	void StopAllActions();
// ----------------------------------------------------------
	// 向该对象发送一个事件，此事件【不可以】向子节点传递
	bool SendEvent(cgGameObjectEvent eventType, int firstParam, int secondParam);

protected:
	// 更新自身，设计上是为了给子类重载用的
	virtual void UpdateSelf(float deltaTime);
	virtual void DoUpdateSelf(float deltaTime);

	// 更新所有的子节点
	void UpdateChildren(float deltaTime);

	// 对子节点排序
	void SortChildrenByDepth();

	// 更新所有的行为
	void UpdateActions(float deltaTime);

	// 渲染
	virtual void RenderSelf();
	virtual void DoRenderSelf(cgCamera * renderCamera);

	// 绘制子节点
	void RenderChildren();

	// 拾取测试，只对位置、范围信息做判断
	bool PickHint(float pointX, float pointY, bool bScreenPoint);

	// 和父节点接触绑定
	void DetachParent();
	void SetParent(cgGameObject * pkParent);
// ----------------------------------------------------------

	// 当父节点的位置（世界位置）变化时
	void OnParentPositionChanged(const cgVector& v);

	// 自身scale发生变化
	void OnScaleChanged(const cgVector& v);

	// 当父节点的缩放（世界缩放）变化时
	void OnParentScaleChanged(const cgVector& v);

	// 当父节点的旋转（世界旋转）时，子节点要做出相应的改变
	void OnParentRotationChanged(float rotation);

	// 当尺寸发生变化时
	virtual void OnSizeChanged();
// ----------------------------------------------------------

	// 把子节点加入列表
	void AddChildToList(cgGameObject * pkChild);
	
	// 事件相关，用于重载
	virtual bool DoProcessEvent(cgGameObjectEvent eventType, int firstParam, int secondParam);

protected:
	string m_strName;
	string m_strLayer;
	
	// 活跃的总时间
	float m_fActiveTime;
	// 深度
	cgGameObjectDepth m_fDepth;
	bool m_bIsDepthDirty; // 子节点的深度有变化，要排序

	// active和visible的区别：
	// 非active的object不绘制，不更新，不响应
	// 非visible的object不绘制，可跟新，不响应
	bool m_bIsActive;
	bool m_bIsVisible;
	bool m_bIsPickable;
	bool m_bIsDestroyed;	// 是否被标记为已销毁
	bool m_bIsEventable;	// 可否接受事件
	
	// 尺寸
	cgSizeF m_kSize;

	// 变换
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
