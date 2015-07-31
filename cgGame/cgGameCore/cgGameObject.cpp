#include "StdAfx.h"
#include "cgGameObject.h"
#include "cgEngineTools.h"
#include "cgCamera.h"
#include "cgGameApp.h"
#include <cgMath.h>
#include "cgCamera.h"
#include <algorithm>

cgGameObjectPtr cgGameObject::ms_spRoot = NULL;

// -----------------------------------------------------------
#ifdef _DEBUG
//#define _DEBUG_LOG_GAME_OBJECT_
#endif
// -----------------------------------------------------------
cgGameObject::cgGameObject(void)
{
	m_strName = "cgGameObject";
	m_fActiveTime = 0.0f;
	m_fDepth = 	cgGameObjectDepth_Defalut;
	m_bIsDepthDirty = false;
	m_bIsActive = true;
	m_bIsVisible = true;
	m_bIsPickable = false;
	m_bIsDestroyed = false;
	m_bIsEventable = false;

	m_pkParent = NULL;
}

cgGameObject::cgGameObject( const string & strName )
{
	m_strName = strName;

	m_fActiveTime = 0.0f;

	m_bIsActive = true;
	m_bIsVisible = true;
	m_bIsPickable = false;
	m_bIsDestroyed = false;
	m_bIsEventable = false;

	m_pkParent = NULL;
}


cgGameObject::~cgGameObject(void)
{
#ifdef _DEBUG_LOG_GAME_OBJECT_
	string strLog ="<cgGameObject>:"+GetName()+"->Destroyed !";
	cout<<strLog.c_str()<<endl;
#endif

}

cgGameObjectPtr cgGameObject::Root()
{
	if (!ms_spRoot)
	{
		ms_spRoot = new cgGameObject("GameRoot");
	}

	return ms_spRoot;
}


void cgGameObject::ClearAll()
{
	if (ms_spRoot)
	{
		ms_spRoot = NULL;
	}
}


cgGameObject * cgGameObject::FindObject( const string & strName )
{
	return cgGameObject::Root()->FindRecursive(strName);
}


// ----------------------------------------------------------

void cgGameObject::Update( float deltaTime )
{
	if (IsActive())
	{
		// 记录自身的活动时间
		m_fActiveTime += deltaTime;

		// 先更新自身，再更新行为列表，最后更新子节点
		UpdateSelf(deltaTime);
		UpdateChildren(deltaTime);
	}
}


void cgGameObject::UpdateChildren( float deltaTime )
{
	if (IsDepthDirty())
	{
		SortChildrenByDepth();
	}

	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end();)
	{
		cgGameObjectPtr spObj = *it;
		spObj->Update(deltaTime);

		if (spObj->IsDestroyed())
			it = m_kChildren.erase(it);
		else
			++it;
	}
}

static bool CmpChildrenByDepth(cgGameObjectPtr l,
	cgGameObjectPtr r)
{
	return l->GetDepth() < r->GetDepth();
}

void cgGameObject::SortChildrenByDepth()
{
	sort(m_kChildren.begin(), m_kChildren.end(), CmpChildrenByDepth);
	m_bIsDepthDirty = false;
}

void cgGameObject::UpdateSelf( float deltaTime )
{
	UpdateActions(deltaTime);
	DoUpdateSelf(deltaTime);
}

void cgGameObject::DoUpdateSelf( float deltaTime )
{
	
}

// ----------------------------------------------------------
#include "cgRender.h"

void cgGameObject::Render()
{
	if (IsActive() && IsVisible())
	{
		RenderSelf();
		RenderChildren();
	}
}


void cgGameObject::RenderSelf()
{
	cgCamera * pkCamera = cgCamera::GetRenderCamera();
	if (!pkCamera)
		return ;

	cgRectF bound;
	if (pkCamera->IsBoundInView(GetBound(bound)))
	{
#ifdef _DEBUG_LOG_GAME_OBJECT_
		if (cgXIsKeyPressed(VK_CONTROL))
		{
			cgVector center = GetWorldPosition();
			if (cgCamera::GetRenderCamera())
				cgCamera::GetRenderCamera()->WorldToScreen(center);
			cgRectF rect(center.x-2, center.y-2, 4, 4);
			cgRender::Get()->FillRect(rect, GetColor());
		}
#endif
		DoRenderSelf(pkCamera);
	}
}

void cgGameObject::DoRenderSelf(cgCamera * renderCamera)
{
}

void cgGameObject::RenderChildren()
{
	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		(*it)->Render();
	}
}

// ----------------------------------------------------------

cgGameObject* cgGameObject::Pick( float pointX, float pointY, bool bScreenPoint)
{
	cgGameObjectPtrList::reverse_iterator it = m_kChildren.rbegin();
	for (; it != m_kChildren.rend(); ++it)
	{
		cgGameObjectPtr pkObj = *it;
		if (!pkObj->IsActive() || !pkObj->IsVisible())
			continue;

		cgGameObject * pkPick = pkObj->Pick(pointX, pointY, bScreenPoint);
		if (pkPick)
			return pkPick;
	}
	if (!IsActive()|| !IsVisible() || !IsPickable() )
		return NULL;

	return PickHint(pointX, pointY, bScreenPoint)?this:NULL;
}


bool cgGameObject::PickHint( float pointX, float pointY, bool bScreenPoint )
{
	if (bScreenPoint)
		return false;

	// todo
	cgVector point(pointX, pointY);

	if (abs(GetWorldRotation())> cgMath::MINI_ROTATION)
	{
		// 如果原始物体有旋转，则反向旋转坐标
		cgXRotateAround(point, -GetWorldRotation(), GetWorldPosition());
	}

	cgRectF bound;
	GetBound(bound);

	return cgMath::IsPointInRect(point, bound);
}

// ----------------------------------------------------------

void cgGameObject::SetName( const string & name )
{
	m_strName = name;
}

const string & cgGameObject::GetName() const
{
	return m_strName;
}

void cgGameObject::SetLayer( const string & layer )
{
	m_strLayer = layer;
}

const string& cgGameObject::GetLayer()
{
	return m_strLayer;
}

string cgGameObject::ToString()
{
	return string("cgGameObject:")+m_strName;
}


// ----------------------------------------------------------
float cgGameObject::GetActiveTime() const
{
	return m_fActiveTime;
}


// ----------------------------------------------------------
void cgGameObject::SetDepth( cgGameObjectDepth depth )
{
	m_fDepth = depth;

	// 深度发生变化，让父节点重新排序
	if (m_pkParent)
		m_pkParent->SetDepthDirty();
}

cgGameObjectDepth cgGameObject::GetDepth() const
{
	return m_fDepth;
}

void cgGameObject::SetDepthDirty()
{
	m_bIsDepthDirty = true;
}

bool cgGameObject::IsDepthDirty() const
{
	return m_bIsDepthDirty;
}

// ----------------------------------------------------------

cgGameObject * cgGameObject::GetParent()
{
	return m_pkParent;
}


void cgGameObject::SetParent( cgGameObject * pkParent )
{
	m_pkParent = pkParent;
	if (m_pkParent)
	{
		OnParentPositionChanged(m_pkParent->GetWorldPosition());
		OnParentScaleChanged(m_pkParent->GetWorldScale());
		OnParentRotationChanged(m_pkParent->GetWorldRotation());
	}
}


cgGameObject * cgGameObject::AttachChild( cgGameObject * pkChild )
{
	pkChild->IncreaseRef();
	pkChild->DetachParent();
	AddChildToList(pkChild);
	pkChild->DecreaseRef();
	return pkChild;
}

cgGameObjectPtr cgGameObject::DetachChild( cgGameObject * pkChild )
{
	cgGameObjectPtr sp = pkChild;
	
	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		if (*it == pkChild)
		{
			m_kChildren.erase(it);
			break;
		}
	}
	return sp;
}


void cgGameObject::DetachAllChild()
{
	m_kChildren.clear();
}

void cgGameObject::DetachParent()
{
	if (m_pkParent)
	{
		m_pkParent->DetachChild(this);
		m_pkParent = NULL;
	}
}

void cgGameObject::AddChildToList( cgGameObject * pkChild )
{
	pkChild->SetParent(this);
	m_kChildren.push_back(pkChild);

	// 添加一个子节点，可能会让子节点排序出现问题
	SetDepthDirty();
}


cgGameObject * cgGameObject::FindChild( const string & strName )
{
	cgGameObject * pkFind = NULL;
	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		cgGameObjectPtr spObj = *it;
		if (spObj->GetName() == strName)
		{
			pkFind = &spObj;
			break;
		}
	}
	return pkFind;
}

// ----------------------------------------------------------

size_t cgGameObject::GetChildCount()
{
	return m_kChildren.size();
}

cgGameObject * cgGameObject::GetChild( size_t index )
{
	if (index >= GetChildCount())
		return NULL;

	return &m_kChildren[index];
}

// ----------------------------------------------------------


cgGameObject * cgGameObject::FindRecursive( const string & strName )
{
	if (GetName() == strName)
		return this;

	cgGameObject * pkFind = NULL;
	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		cgGameObjectPtr spObj = *it;
		pkFind = spObj->FindRecursive(strName);
		if (pkFind)
			return pkFind;
	}

	return NULL;
}

// ----------------------------------------------------------

// 变换操作
const cgTransform& cgGameObject::GetWorldTransform() const
{
	return m_kWorldTransform;
}

const cgTransform& cgGameObject::GetLocalTransform() const
{
	return m_kLocalTransform;
}
// ----------------------------------------------------------

// 世界位置
void cgGameObject::SetWorldPosition( const cgVector& pos )
{
	Move(pos-GetWorldPosition());
}

void cgGameObject::SetWorldPosition( float x, float y )
{
	SetWorldPosition(cgVector(x, y));
}

const cgVector& cgGameObject::GetWorldPosition() const
{
	return m_kWorldTransform.pos;
}
// ----------------------------------------------------------

// 相对于父节点位置
void cgGameObject::SetLocalPosition( const cgVector& pos )
{
	Move(pos-GetLocalPosition());
}

void cgGameObject::SetLocalPosition( float x, float y )
{
	SetLocalPosition(cgVector(x, y));
}

const cgVector& cgGameObject::GetLocalPosition() const
{
	return m_kLocalTransform.pos;
}

// ----------------------------------------------------------

// 移动
void cgGameObject::Move( const cgVector & v )
{
	m_kLocalTransform.pos += v;
	m_kWorldTransform.pos += v;

	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		(*it)->OnParentPositionChanged(v);
	}
}

void cgGameObject::Move( float deltaX, float deltaY )
{
	Move(cgVector(deltaX, deltaY));
}

void cgGameObject::OnParentPositionChanged( const cgVector& v )
{
	m_kWorldTransform.pos += v;

	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		(*it)->OnParentPositionChanged(v);
	}

}

// ----------------------------------------------------------

// 世界缩放
void cgGameObject::SetWorldScale( const cgVector& scale )
{
	SetLocalScale(m_pkParent?scale/m_pkParent->GetWorldScale():scale);
}

void cgGameObject::SetWorldScale( float scaleX, float scaleY )
{
	SetWorldScale(cgVector(scaleX, scaleY));
}

const cgVector& cgGameObject::GetWorldScale() const
{
	return m_kWorldTransform.scale;
}
// ----------------------------------------------------------

// 本地缩放
void cgGameObject::SetLocalScale( const cgVector & scale )
{
	LocalScale(scale-GetLocalScale());
}

void cgGameObject::SetLocalScale( float scaleX, float scaleY )
{
	SetLocalScale(cgVector(scaleX, scaleY));
}

const cgVector& cgGameObject::GetLocalScale()
{
	return m_kLocalTransform.scale;
}

// ----------------------------------------------------------

// 缩放
void cgGameObject::LocalScale( const cgVector & scale )
{
	m_kLocalTransform.scale += scale;
	m_kWorldTransform.scale = m_pkParent?GetLocalScale()*m_pkParent->GetWorldScale():GetLocalScale();

	OnScaleChanged(scale);
}

void cgGameObject::LocalScale( float scaleX, float scaleY )
{
	LocalScale(cgVector(scaleX, scaleY));
}

void cgGameObject::WorldScale( const cgVector & scale )
{
	m_kWorldTransform.scale += scale;
	m_kLocalTransform.scale = m_pkParent?GetWorldScale()/m_pkParent->GetWorldScale():GetWorldScale();
	
	OnScaleChanged(scale);
}

void cgGameObject::WorldScale( float scaleX, float scaleY )
{
	WorldScale(cgVector(scaleX, scaleY));
}


void cgGameObject::OnScaleChanged( const cgVector& v )
{
	m_kLocalTransform.scale.x = max(m_kLocalTransform.scale.x, cgMath::MINI_SCALE);
	m_kLocalTransform.scale.y = max(m_kLocalTransform.scale.y, cgMath::MINI_SCALE);
	m_kWorldTransform.scale.x = max(m_kWorldTransform.scale.x, cgMath::MINI_SCALE);
	m_kWorldTransform.scale.y = max(m_kWorldTransform.scale.y, cgMath::MINI_SCALE);

	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		(*it)->OnParentScaleChanged(v);
	}
}

// 父节点的缩放发生变化，重新计算自身的世界缩放
// localpostion也会变化，缩放的变化和localpos时等比的
void cgGameObject::OnParentScaleChanged( const cgVector& v )
{
	cgVector targetScale = GetLocalScale()*m_pkParent->GetWorldScale();
	m_kLocalTransform.pos = m_kLocalTransform.pos*(targetScale/GetWorldScale());
	m_kWorldTransform.pos = GetLocalPosition()+m_pkParent->GetWorldPosition();
	m_kWorldTransform.scale = targetScale;

	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		(*it)->OnParentScaleChanged(v);
	}
}

// ----------------------------------------------------------


void cgGameObject::SetWorldRotation( float rotation )
{
	Rotate(rotation-GetWorldRotation());
}

float cgGameObject::GetWorldRotation() const
{
	return m_kWorldTransform.rotation;
}

void cgGameObject::SetLocalRotation( float rotation )
{
	Rotate(rotation-GetLocalRotation());
}

float cgGameObject::GetLocalRotation()
{
	return m_kLocalTransform.rotation;
}

// ----------------------------------------------------------

void cgGameObject::Rotate( float rotation )
{
	m_kLocalTransform.rotation += rotation;
	m_kWorldTransform.rotation = m_pkParent?(GetLocalRotation()+m_pkParent->GetWorldRotation()):GetLocalRotation();

	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		(*it)->OnParentRotationChanged(rotation);
	}
}

void cgGameObject::OnParentRotationChanged(float rotation)
{
	// localrotation不变，rotation重新计算
	m_kWorldTransform.rotation = GetLocalRotation()+m_pkParent->GetWorldRotation();

	// localposition发生旋转，worldposition重新计算
	cgXRotate(m_kLocalTransform.pos, rotation);
	m_kWorldTransform.pos = GetLocalPosition() + m_pkParent->GetWorldPosition();

	cgGameObjectPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		(*it)->OnParentRotationChanged(rotation);
	}

}

// ----------------------------------------------------------

// 绕着某个位置旋转，分两步走：
// 1、位置先根据旋转放好
// 2、自身旋转
void cgGameObject::RotateAround( float rotation, const cgVector& centerV )
{
	// 先把位置调好，然后再说旋转，
	// 因为旋转时子节点的localpostion旋转，postion会重新计算
	// 所以这里发生了位置变化不用通知子节点
	cgXRotateAround(m_kWorldTransform.pos, rotation, centerV);
	m_kLocalTransform.pos = m_pkParent?(GetWorldPosition()-m_pkParent->GetWorldPosition()):GetWorldPosition();

	Rotate(rotation);
}

void cgGameObject::RotateAround( float rotation, float centerX, float centerY )
{
	RotateAround(rotation, cgVector(centerX, centerY));
}

// ----------------------------------------------------------
void cgGameObject::SetSize( const cgSizeF & size )
{
	SetSize(size.w, size.h);
}

void cgGameObject::SetSize( float w, float h )
{
	m_kSize.Set(w, h);

	OnSizeChanged();
}

const cgSizeF& cgGameObject::GetSize()
{
	return m_kSize;
}


void cgGameObject::OnSizeChanged()
{

}

// ----------------------------------------------------------

const cgRectF& cgGameObject::GetBound( cgRectF& rect )const
{
	rect.w = m_kSize.w*GetWorldScale().x;
	rect.h = m_kSize.h*GetWorldScale().y;
	rect.x = GetWorldPosition().x-rect.w/2.0f;
	rect.y = GetWorldPosition().y-rect.h/2.0f;

	return rect;
}

// ----------------------------------------------------------

void cgGameObject::SetColor( cgColor color )
{
	m_kRenderProp.color = color;
}

cgColor cgGameObject::GetColor()
{
	return m_kRenderProp.color;
}

void cgGameObject::SetAlpha( float alpha )
{
	m_kRenderProp.alpha = alpha;
}

float cgGameObject::GetAlpha()
{
	return m_kRenderProp.alpha;
}


void cgGameObject::Alpha( float deltaAlpha )
{
	m_kRenderProp.alpha += deltaAlpha;
}


cgColor cgGameObject::GetRenderColor()
{
	if (m_kRenderProp.alpha< 0.0f)
		m_kRenderProp.alpha = 0.0f;
	if (m_kRenderProp.alpha > 1.0f)
		m_kRenderProp.alpha = 1.0f;

	return (m_kRenderProp.color&0x00ffffff)|
		(( static_cast<unsigned>( 255*m_kRenderProp.alpha) )<<24);
}

// ----------------------------------------------------------

bool cgGameObject::IsActive()
{
	return m_bIsActive;
}

void cgGameObject::SetActive( bool bActive )
{
	m_bIsActive = bActive;
	// todo 激活的时候会触发时间
}

bool cgGameObject::IsVisible()
{
	return m_bIsVisible;
}

void cgGameObject::SetVisible( bool bVisible )
{
	m_bIsVisible = bVisible;
}


bool cgGameObject::IsPickable()
{
	return m_bIsPickable;
}

void cgGameObject::SetPickable( bool bPickable )
{
	m_bIsPickable = bPickable;
	// todo
}


void cgGameObject::Destroy()
{
	m_bIsDestroyed = true;
}

bool cgGameObject::IsDestroyed()
{
	return m_bIsDestroyed;
}


void cgGameObject::SetEventable( bool eventable )
{
	m_bIsEventable = eventable;
}

bool cgGameObject::IsEventable()
{
	return m_bIsEventable;
}

// ----------------------------------------------------------

cgAction * cgGameObject::StartAction( cgAction * pkAction )
{
	if (pkAction)
	{
		m_kActionList.push_back(pkAction);
		pkAction->SetObject(this);
		pkAction->Start();
	}
	return pkAction;
}

cgAction * cgGameObject::FindAction( const string& strName )
{
	cgActionPtrList::iterator it = m_kActionList.begin();
	for (; it != m_kActionList.end(); ++it)
	{
		cgActionPtr spAction = *it;
		if (spAction->GetName() == strName)
			return &spAction;
	}

	return NULL;
}

size_t cgGameObject::GetActionCount()
{
	return m_kActionList.size();
}

void cgGameObject::StopAction( const string & strName )
{
	cgAction * pkAction = FindAction(strName);
	if (pkAction)
	{
		pkAction->Stop();
	}
}

void cgGameObject::StopAllActions()
{
	cgActionPtrList::iterator it = m_kActionList.begin();
	for (; it != m_kActionList.end(); ++it)
	{
		(*it)->Stop();
	}
}

void cgGameObject::UpdateActions( float deltaTime )
{
	cgActionPtrList::iterator it = m_kActionList.begin();
	while( it != m_kActionList.end())
	{
		cgActionPtr spAction = *it;

		if (spAction->IsActive())
		{
			spAction->Update(deltaTime);
		}
		if (spAction->IsStopped())
		{
			it = m_kActionList.erase(it);
		}else
		{
			++it;
		}
	}
}

// ----------------------------------------------------------

bool cgGameObject::SendEvent( cgGameObjectEvent eventType, int firstParam, int secondParam )
{
	if (!IsActive() || !IsEventable())
		return false;

	return DoProcessEvent(eventType, firstParam, secondParam);
}

bool cgGameObject::DoProcessEvent( cgGameObjectEvent eventType, int firstParam, int secondParam )
{
	return false;
}




