#include "StdAfx.h"
#include "cgUIWidget.h"
#include "cgUIImage.h"
#include "cgUIRender.h"
#include "cgUIManager.h"
#include "cgEngineTools.h"
#include <algorithm>
#include <cgCursorManager.h>


cgUIWidget::cgUIWidget(void)
{
	SetupParams();
	m_strName = "cgUIWidget";
}

cgUIWidget::cgUIWidget( const string& strName )
{
	SetupParams();
	m_strName = strName;
}


cgUIWidget::~cgUIWidget(void)
{
}


void cgUIWidget::SetupParams()
{
	m_nDepth = 0;

	m_nState = cgUIState_Visible|cgUIState_Enable;
	m_nDrawFlag = 0;
	m_nStyle = 0;
	m_nExtendStyle = 0;
	m_idFont = 0;
	m_nTextStyle = DT_CENTER|DT_VCENTER;
	m_nTextRowSpace = 5;

	m_strCursor = "IDC_ARROW";

	m_uTextColor = 0xfe000000;
	m_uBackColor = 0xffffffff;
	m_uBorderColor = 0xffcfcfcf;
	m_nCustomType = -1;
	m_nCustomValue = -1;
	m_pkParent = NULL;
}

// --------------------------------------------------------------------------------------------
bool cgUIWidget::OnMessage( cgUIMsg msg, unsigned wparam, unsigned lparam )
{
	int x = LOWORD(lparam);
	int y = HIWORD(lparam);
	switch (msg)
	{
	case WM_MOUSEMOVE:
		{
			cgCursorManager::Get()->SetCursor(m_strCursor);

			if ( IsClickDown() && IsMovable() )
			{
				int posX = IsXMove()?x+m_kDistanceToMouseDown.x:GetX();
				int posY = IsYMove()?y+m_kDistanceToMouseDown.y:GetY();
				SetPosition(posX, posY);
				return true;
			}
		}break;
	case WM_KEYDOWN:
		{
			switch (wparam)
			{
			case VK_RETURN:
				{
					ReportUIEvent(cgUIEvent_OnEnter);
					return true;
				}break;
			case VK_TAB:
				{
					ReportUIEvent(cgUIEvent_OnTab);
					return true;
				}break;
			default:
				break;
			}
			return false;
		}break;
	case WM_LBUTTONDBLCLK:
		{
			ReportUIEvent(cgUIEvent_OnDbClick);
			return true;
		}break;
	case WM_LBUTTONDOWN:
		{
			if (m_nStyle&cgUIStyle_XMove || m_nStyle&cgUIStyle_YMove)
			{
				m_kDistanceToMouseDown.x = GetX()-x;
				m_kDistanceToMouseDown.y = GetY()-y;
			}

			SetClickDown(true);
			return true;
		}break;
	case WM_LBUTTONUP:
		{
			if (IsClickDown())
			{
				SetClickDown(false);
				ReportUIEvent(cgUIEvent_OnClick);
			}

			return true;
		}break;
	case cgUIMsg_MouseIn:
		{
			SetMouseOver(true);
			ReportUIEvent(cgUIEvent_OnMouseIn);

			// 如果是在一个控件上面点击，然后按住鼠标出去，再回来
			// 应该会变成选中状态
			if ((wparam&MK_LBUTTON) !=0 && IsFocus())
				SetClickDown(true);

			cgCursorManager::Get()->SetCursor(m_strCursor);

			return true;
		}break;
	case cgUIMsg_MouseOut:
		{
			SetMouseOver(false);
			ReportUIEvent(cgUIEvent_OnMouseOut);

			// 如果是在一个控件上面点击，然后按住鼠标出去
			// 选中状态取消
			if (IsClickDown())
				SetClickDown(false);

			cgCursorManager::Get()->Reset();

			return true;
		}
		break;
	case cgUIMsg_GainFocus:
		{
			SetFocus(true);
			ReportUIEvent(cgUIEvent_OnGainFocus);
			return true;
		}
		break;
	case cgUIMsg_LostFocus:
		{
			SetFocus(false);
			ReportUIEvent(cgUIEvent_OnLostFocus);
			return true;
		}
		break;
	case cgUIMsg_Copy:
		{
			return OnCopy();
		}
		break;
	case cgUIMsg_Cut:
		{
			return OnCut();
		}
		break;
	case cgUIMsg_Paste:
		{
			return OnPaste();
		}break;

	default:
		break;
	}

	cgUIWidgetPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		cgUIWidgetPtr & ptr = *it;
		if (ptr && ptr->IsVisible())
			if (ptr->OnMessage(msg, wparam, lparam))
				return true;
	}

	return false;
}

void cgUIWidget::Update( float fTime )
{
	// 如果深度有变化
	if (IsChildrenDepthDirty())
	{
		SortChildrenByDepth();
		SetChildrenDepthDirty(false);
	}

	// 先更新自己
	UpdateSelf(fTime);
	UpdateChildren(fTime);
	
}


void cgUIWidget::UpdateSelf( float fTime )
{

}


void cgUIWidget::UpdateChildren( float fTime )
{
	// 递归更新子控件
	cgUIWidgetPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		cgUIWidgetPtr & ptr = *it;
		if (ptr && ptr->IsVisible())
			ptr->Update(fTime);
	}
}

// 深度比较函数
static bool CmpUIDepth(cgUIWidgetPtr l, cgUIWidgetPtr r)
{
	return l->GetDepth() < r->GetDepth();
}

void cgUIWidget::SortChildrenByDepth()
{
	std::sort(m_kChildren.begin(), m_kChildren.end(), CmpUIDepth);
}


// ------------------------------------------------------------------------------------------

void cgUIWidget::Render( const cgRectF& dirtyRect )
{
	// 先自己绘制
	RenderSelf(dirtyRect);

	// 递归绘制子控件
	RenderChildren(dirtyRect);

	// 边框最后绘制
	DrawBorder(dirtyRect);
}


void cgUIWidget::RenderSelf(const cgRectF& dirtyRect)
{
	// 手工剪切总是难剪切精细，可以用这个来强制剪切
	if (IfClipSelf() )
	{
		if (!cgUIRender::GetRender()->PushClipRect(m_kRect))
			return;
	}

	cgRectF clipRect;
	if (!cgXGetIntersectRect(dirtyRect, m_kRect, clipRect))
		return;

// -----------------------------------------------------------------------------
	DrawBackground(clipRect);
	DrawBackPic(clipRect);
	DrawText(clipRect);
// -----------------------------------------------------------------------------

	if (IfClipSelf())
		cgUIRender::GetRender()->PopClipRect();

#ifdef _DEBUG
	if (cgUIManager::Get()->IsInEditMode())
	{
		cgUIRender::GetRender()->DrawBox(m_kRect, 0xff00ffff);
		cgUIRender::GetRender()->DrawBox(clipRect, 0xffff00ff);
	}
#endif
}


void cgUIWidget::RenderChildren( const cgRectF& dirtyRect )
{
	if (IfClipChildren() && !cgUIRender::GetRender()->PushClipRect(m_kRect))
		return ;

	cgUIWidgetPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		cgUIWidgetPtr & ptr = *it;
		if (ptr && ptr->IsVisible())
			ptr->Render(dirtyRect);
	}

	if (IfClipChildren())
		cgUIRender::GetRender()->PopClipRect();
}

// -----------------------------------------------------------------------------

void cgUIWidget::DrawBorder( const cgRectF& clipRect )
{
	if (IfDrawBorder())
	{
		// border不能出rect区域
		cgUIRender::GetRender()->DrawBox(cgRectF(m_kRect.x, m_kRect.y, m_kRect.w-1, m_kRect.h-1), m_uBorderColor);

#ifdef _DEBUG
		if (cgUIManager::Get()->IsInEditMode())
		{
			if (IsMouseOver())
				cgUIRender::GetRender()->DrawBox(cgRectF(m_kRect.x, m_kRect.y, m_kRect.w-1, m_kRect.h-1), 0x8fff0000);
			if (IsFocus())
				cgUIRender::GetRender()->DrawBox(cgRectF(m_kRect.x, m_kRect.y, m_kRect.w-1, m_kRect.h-1), 0x8f00ff00);
		}
#endif
	}
}


void cgUIWidget::DrawBackground(const cgRectF& clipRect)
{
	if (IfFillBackground())
		cgUIRender::GetRender()->FillRect(clipRect, m_uBackColor);
}

void cgUIWidget::DrawBackPic(const cgRectF& clipRect)
{
	DoDrawPic(m_spBkImage, m_kRect, clipRect);
}

bool cgUIWidget::DoDrawPic( cgUIImagePtr spPic, const cgRectF& boundRect, const cgRectF& clipRect)
{
	if (!spPic)
		return false;

	if (IsAutoScale())
	{
		cgRectF srcRect((clipRect.x-boundRect.x)*spPic->GetWidth()/boundRect.w,
			(clipRect.y-boundRect.y)*spPic->GetHeight()/boundRect.h,
			clipRect.w*spPic->GetWidth()/boundRect.w,
			clipRect.h*spPic->GetHeight()/boundRect.h);

		spPic->Draw(srcRect, clipRect);
	}
	else
	{
		cgRectF srcRect(clipRect.x-boundRect.x, clipRect.y-boundRect.y, clipRect.w, clipRect.h);
		srcRect.w = min(srcRect.w, spPic->GetWidth()-srcRect.x);
		srcRect.h = min(srcRect.h, spPic->GetHeight()-srcRect.y);

		cgRectF destRect = clipRect;
		destRect.w = srcRect.w;
		destRect.h = srcRect.h;

		spPic->Draw(srcRect, destRect);
	//	spPic->Draw(srcRect, clipRect);
	}

	return true;
}


void cgUIWidget::DrawText(const cgRectF& clipRect)
{
	// cg_todo
	cgUIRender::GetRender()->DrawUIText(m_strText.c_str(), m_strText.length(),
		m_kRect, m_idFont, m_nTextRowSpace, m_uTextColor, m_nTextStyle);
}

// -------------------------------------------------------------------------------------------
void cgUIWidget::AddChild( cgUIWidgetPtr spChild )
{
	if (spChild)
	{
		m_kChildren.push_back(spChild);
		spChild->SetParent(this);
		SetChildrenDepthDirty(true);
	}
}

unsigned cgUIWidget::GetChildNum()
{
	return m_kChildren.size();
}


void cgUIWidget::DelChild( cgUIWidgetPtr spChild )
{
	// 递归更新子控件
	cgUIWidgetPtrList::iterator it = m_kChildren.begin();
	for (; it != m_kChildren.end(); ++it)
	{
		cgUIWidgetPtr & ptr = *it;
		if (ptr == spChild)
		{
			m_kChildren.erase(it);
			break;
		}
	}
}


void cgUIWidget::SetParent( cgUIWidget* pkParent )
{
	m_pkParent = pkParent;
	// 当自己被添加到一个父窗口时，自身需要重新
	if (m_pkParent)
	{
		OnParentMoved();
		ReportDirty();
	}
}

cgUIWidget* cgUIWidget::GetParent()
{
	return m_pkParent;
}

// -------------------------------------------------------------------------------------------
bool cgUIWidget::IsVisible()const
{
	return (m_nState&cgUIState_Visible) != 0;
}

void cgUIWidget::SetVisible( bool bVisible )
{
	if (IsVisible() != bVisible)
	{
		if (bVisible)
			m_nState |= cgUIState_Visible;
		else
			m_nState &= ~cgUIState_Visible;

		ReportDirty();
	}
}

bool cgUIWidget::IsFocus()const
{
	return (m_nState&cgUIState_Focus) != 0;
}

void cgUIWidget::SetFocus( bool bFocus )
{
	if (IsFocus() != bFocus)
	{
		if (bFocus)
			m_nState |= cgUIState_Focus;
		else
			m_nState &= ~cgUIState_Focus;

		ReportDirty();
	}
}

bool cgUIWidget::IsMouseOver()const
{
	return (m_nState&cgUIState_MouseOver) != 0;
}

void cgUIWidget::SetMouseOver( bool bOver )
{
	if (IsMouseOver() != bOver)
	{
		if (bOver)
			m_nState |= cgUIState_MouseOver;
		else
			m_nState &= ~cgUIState_MouseOver;

		ReportDirty();
	}
	
}


bool cgUIWidget::IsClickDown()const
{
	return (m_nState&cgUIState_ClickDown) != 0;
}

void cgUIWidget::SetClickDown( bool bClick )
{
	if (IsClickDown() != bClick)
	{
		if (bClick)
			m_nState |= cgUIState_ClickDown;
		else
			m_nState &= ~cgUIState_ClickDown;

		ReportDirty();
	}
	
}

bool cgUIWidget::IsEnable()const
{
	return (m_nState&cgUIState_Enable) != 0;
}

void cgUIWidget::SetEnable( bool bEnable )
{
	if (IsEnable() != bEnable)
	{
		if (bEnable)
			m_nState |= cgUIState_Enable;
		else
			m_nState &= ~cgUIState_Enable;

		ReportDirty();
	}
	
}


bool cgUIWidget::IsChildrenDepthDirty() const
{
	return (m_nState&cgUIState_DepthDirty) != 0;
}

void cgUIWidget::SetChildrenDepthDirty( bool bDirty )
{
	if (IsChildrenDepthDirty() != bDirty)
	{
		if (bDirty)
			m_nState |= cgUIState_DepthDirty;
		else
			m_nState &= ~cgUIState_DepthDirty;

		ReportDirty();
	}

}

int cgUIWidget::GetState()const
{
	return m_nState;
}

void cgUIWidget::SetState( int nState )
{
	if (m_nState != nState)
	{
		m_nState = nState;

		ReportDirty();
	}
}

// ---------------------------------------------------------------------------

bool cgUIWidget::IsStatic()const
{
	return (m_nStyle&cgUIStyle_Static) != 0;
}

void cgUIWidget::SetStatic( bool bStatic )
{
	if (IsStatic() != bStatic)
	{
		if (bStatic)
			m_nStyle |= cgUIStyle_Static;
		else
			m_nStyle &= ~cgUIStyle_Static;

		ReportDirty();
	}
}

bool cgUIWidget::IsXMove()
{
	return (m_nStyle&cgUIStyle_XMove) != 0;
}

void cgUIWidget::SetXMove( bool bMove )
{
	if (IsXMove() != bMove)
	{
		if (bMove)
			m_nStyle |= cgUIStyle_XMove;
		else
			m_nStyle &= ~cgUIStyle_XMove;

		ReportDirty();
	}
}

bool cgUIWidget::IsYMove()
{
	return (m_nStyle&cgUIStyle_YMove) != 0;
}

void cgUIWidget::SetYMove( bool bMove )
{
	if (IsYMove() != bMove)
	{
		if (bMove)
			m_nStyle |= cgUIStyle_YMove;
		else
			m_nStyle &= ~cgUIStyle_YMove;

		ReportDirty();
	}
}

bool cgUIWidget::IsMovable()
{
	return IsXMove() || IsYMove();
}

void cgUIWidget::SetMovable(bool bMove)
{
	SetXMove(bMove);
	SetYMove(bMove);
}

int cgUIWidget::GetStyle() const
{
	return m_nStyle;
}

void cgUIWidget::SetStyle( int nStyle )
{
	if (nStyle != m_nStyle)
	{
		m_nStyle = nStyle;
		ReportDirty();
	}
}

// ---------------------------------------------------------------------------

bool cgUIWidget::IsAutoScale()const
{
	return (m_nDrawFlag&cgUIDrawFlag_AutoScale) != 0;
}

void cgUIWidget::SetAutoScale( bool bAuto )
{
	if (IsAutoScale() != bAuto)
	{
		if (bAuto)
			m_nDrawFlag |= cgUIDrawFlag_AutoScale;
		else
			m_nDrawFlag &= cgUIDrawFlag_AutoScale;

		ReportDirty();
	}
	
}

bool cgUIWidget::IfFillBackground()const
{
	return (m_nDrawFlag&cgUIDrawFlag_DrawBackColor) != 0;
}

void cgUIWidget::SetDrawBackColor( bool bFill )
{
	if (IfFillBackground() != bFill)
	{
		if (bFill)
			m_nDrawFlag |= cgUIDrawFlag_DrawBackColor;
		else
			m_nDrawFlag &= cgUIDrawFlag_DrawBackColor;

		ReportDirty();
	}
}

bool cgUIWidget::IfDrawBorder() const
{
	return (m_nDrawFlag&cgUIDrawFlag_DrawBorder) != 0;
}

void cgUIWidget::SetDrawBorder( bool bDraw )
{
	if (IfDrawBorder() != bDraw)
	{
		if (bDraw)
			m_nDrawFlag |= cgUIDrawFlag_DrawBorder;
		else
			m_nDrawFlag &= cgUIDrawFlag_DrawBorder;

		ReportDirty();
	}
}

bool cgUIWidget::IfClipSelf() const
{
	return (m_nDrawFlag&cgUIDrawFlag_ClipSelf) != 0;
}

void cgUIWidget::SetClipSelf( bool bClip )
{
	if (IfClipSelf() != bClip)
	{
		if (bClip)
			m_nDrawFlag |= cgUIDrawFlag_ClipSelf;
		else
			m_nDrawFlag &= cgUIDrawFlag_ClipSelf;

		ReportDirty();
	}
}

bool cgUIWidget::IfClipChildren() const
{
	return (m_nDrawFlag&cgUIDrawFlag_ClipChildren) != 0;
}

void cgUIWidget::SetClipChildren( bool bClip )
{
	if (IfClipChildren() != bClip)
	{
		if (bClip)
			m_nDrawFlag |= cgUIDrawFlag_ClipChildren;
		else
			m_nDrawFlag &= cgUIDrawFlag_ClipChildren;

		ReportDirty();
	}
}

int cgUIWidget::GetDrawFlag()const
{
	return m_nDrawFlag;
}

void cgUIWidget::SetDrawFlag( int nFlag )
{
	if (m_nDrawFlag != nFlag)
	{
		m_nDrawFlag = nFlag;
		ReportDirty();
	}
}


// ---------------------------------------------------------------------------


int cgUIWidget::GetExtendStyle()const
{
	return m_nExtendStyle;
}

void cgUIWidget::SetExtendStyle( int nExtendStyle )
{
	if (nExtendStyle != m_nExtendStyle)
	{
		m_nExtendStyle = nExtendStyle;

		ReportDirty();
	}
}

// -------------------------------------------------------------------------------------------

void cgUIWidget::SetRect( int x, int y, int w, int h )
{
	SetPosition(x, y);
	SetSize(w, h);
}

void cgUIWidget::SetRect( const cgRectF & rect )
{
	SetRect(m_kRect.x, m_kRect.y, m_kRect.w, m_kRect.h);
}

void cgUIWidget::SetPosition( int x, int y )
{
	Move( x-m_kRect.x, y-m_kRect.y);
}

void cgUIWidget::SetPosition( const cgPoint & point )
{
	SetPosition(point.x, point.y);
}


void cgUIWidget::SetLocalRect( int x, int y, int w, int h )
{
	SetLocalPosition(x, y);
	SetSize(w, h);
}

void cgUIWidget::SetLocalPosition( int x, int y )
{
	Move( x-m_kLocalRect.x, y-m_kLocalRect.y);
}

void cgUIWidget::Move( int x, int y )
{
	if (x == 0 && y == 0)
		return ;

	MoveSelf(x, y);
	MoveChildren();
}


void cgUIWidget::MoveSelf( int x, int y )
{
	ReportDirty();
	m_kRect.x += x;
	m_kRect.y += y;
	m_kLocalRect.x += x;
	m_kLocalRect.y += y;
	ReportDirty();

	OnPositionChanged();
}

void cgUIWidget::MoveChildren()
{
	cgUIWidgetPtrList::iterator it = m_kChildren.begin();
	for ( ; it != m_kChildren.end(); ++it)
	{
		cgUIWidgetPtr & spChild = *it;
		if (spChild)
			spChild->OnParentMoved();
	}
}

void cgUIWidget::OnPositionChanged()
{

}

void cgUIWidget::OnParentMoved()
{
	// 本地坐标不变，世界坐标重新计算
	ReportDirty();
	m_kRect.x = m_kLocalRect.x + m_pkParent->GetX();
	m_kRect.y = m_kLocalRect.y + m_pkParent->GetY();
	ReportDirty();

	OnPositionChanged();

	MoveChildren();
}


void cgUIWidget::SetSize( int w, int h )
{
	if (m_kRect.w != w || m_kRect.h != h)
	{
		ReportDirty();

		m_kRect.w = w;
		m_kRect.h = h;
		m_kLocalRect.w = w;
		m_kLocalRect.h = h;
		ReportDirty();

		OnSizeChanged();
	}

}

void cgUIWidget::OnSizeChanged()
{

}


void cgUIWidget::SetSize( const cgSize& size )
{
	SetSize(size.w, size.h);
}

int cgUIWidget::GetX()const
{
	return m_kRect.x;
}

int cgUIWidget::GetY()const
{
	return m_kRect.y;
}

int cgUIWidget::GetWidth()const
{
	return m_kRect.w;
}

int cgUIWidget::GetHeight()const
{
	return m_kRect.h;
}

cgRectF cgUIWidget::GetRect() const
{
	return m_kRect;
}

cgPoint cgUIWidget::GetPosition() const
{
	return cgPoint(m_kRect.x, m_kRect.y);
}

cgSize cgUIWidget::GetSize() const
{
	return cgSize(m_kRect.w, m_kRect.h);
}

void cgUIWidget::SetDepth( int depth )
{
	if (m_nDepth != depth)
	{
		m_nDepth = depth;
		if (m_pkParent)
			m_pkParent->SetChildrenDepthDirty(true);
	}
}

int cgUIWidget::GetDepth() const
{
	return m_nDepth;
}

// -------------------------------------------------------------------------------------------

void cgUIWidget::SetBackPic( LPCTSTR path )
{
	m_spBkImage = new cgUIImage(path);
	ReportDirty();
}

void cgUIWidget::SetBackPic( cgID resID )
{
	m_spBkImage = new cgUIImage(resID);
	ReportDirty();
}

// -------------------------------------------------------------------------------------

void cgUIWidget::SetText( LPCTSTR text )
{
	m_strText = text;

	OnTextChanged();
	ReportUIEvent(cgUIEvent_OnTextChange);
	ReportDirty();
}

LPCTSTR cgUIWidget::GetText()const
{
	return m_strText.c_str();
}

void cgUIWidget::SetFont( cgID id )
{
	m_idFont = id;

	OnFontChanged();
	ReportDirty();
}

cgID cgUIWidget::GetFont()const
{
	return m_idFont;
}

void cgUIWidget::SetTextStyle( int nStyle )
{
	m_nTextStyle = nStyle;

	OnTextStyleChanged();
	ReportDirty();
}

int cgUIWidget::GetTextStyle()const
{
	return m_nTextStyle;
}

int cgUIWidget::GetTextRowSpace()const
{
	return m_nTextRowSpace ;
}

void cgUIWidget::SetTextRowSpace( int nSpace )
{
	m_nTextRowSpace = nSpace;

	OnTextRowSpaceChanged();
	ReportDirty();
}

void cgUIWidget::SetTextColor( cgColor color )
{
	// 最大的alpha值为254，防止gdiplus界面文字穿透
	m_uTextColor = color&0xfeffffff;

	OnTextColorChanged();
	ReportDirty();
}

cgColor cgUIWidget::GetTextColor()const
{
	return m_uTextColor;
}

// -------------------------------------------------------------------------------------

void cgUIWidget::SetBackColor( cgColor color )
{
	m_uBackColor = color;
	ReportDirty();
}

cgColor cgUIWidget::GetBackColor()const
{
	return m_uBackColor;
}

void cgUIWidget::SetBorderColor( cgColor color )
{
	m_uBorderColor = color;
	ReportDirty();
}

cgColor cgUIWidget::GetBorderColor() const
{
	return m_uBorderColor;
}

// -------------------------------------------------------------------------------------

void cgUIWidget::SetName( const string & strID )
{
	m_strName = strID;
}

const string& cgUIWidget::GetName()
{
	return m_strName;
}

void cgUIWidget::SetCursor( const string & strCursor )
{
	m_strCursor = strCursor;
}

const string& cgUIWidget::GetCursor()
{
	return m_strCursor;
}


void cgUIWidget::GetPath(string & path)
{
	if (m_pkParent)
	{
		m_pkParent->GetPath(path);
		path = path+"."+m_strName;
	}else
	{
		path = m_strName;
	}
}

// -------------------------------------------------------------------------------------

void cgUIWidget::SetCustomType( int nType )
{
	m_nCustomType = nType;
}

int cgUIWidget::GetCustomType()const
{
	return m_nCustomType;
}

void cgUIWidget::SetCustomValue( int nValue )
{
	m_nCustomValue = nValue;
}

int cgUIWidget::GetCustomValue()const
{
	return m_nCustomValue;
}

void cgUIWidget::SetCustomString( const cgString& str )
{
	m_strCustomString = str;
}

const cgString & cgUIWidget::GetCustomString()const
{
	return m_strCustomString;
}

// -------------------------------------------------------------------------------------

cgUIWidgetPtr cgUIWidget::FindComponent( const char * path )
{
	const char* next = strchr(path, '.');
	if (!next)
	{
		if (strcmp(path, m_strName.c_str()) == 0)
			return this;

	}else if (strncmp(path, m_strName.c_str(), next-path) == 0)
	{
		cgUIWidgetPtrList::iterator it = m_kChildren.begin();
		for ( ; it != m_kChildren.end(); ++it)
		{
			cgUIWidgetPtr & spChild = *it;
			if (!spChild)
				continue;

			cgUIWidgetPtr spMouseComponent = spChild->FindComponent(next+1);
			if (spMouseComponent)
				return spMouseComponent;
		}
	}

	return NULL;
}

cgUIWidgetPtr cgUIWidget::FindChild( const char * path )
{
	cgUIWidgetPtrList::iterator it = m_kChildren.begin();
	for ( ; it != m_kChildren.end(); ++it)
	{
		cgUIWidgetPtr & spChild = *it;
		if (!spChild)
			continue;

		cgUIWidgetPtr spMouseComponent = spChild->FindComponent(path);
		if (spMouseComponent)
			return spMouseComponent;
	}

	return NULL;
}

cgUIWidgetPtr cgUIWidget::Pick( int x, int y )
{
	// 如果剪切子节点，那么拾取时也应该剪切
	if (IfClipChildren() && !IsPointIn(x, y))
		return NULL;

	// 优先找子节点
	cgUIWidgetPtr spPick = PickInChildren(x, y);
	if (spPick)
		return spPick;

	// 如果是static，不响应，也不可被拾取
	if (IsVisible() && !IsStatic() && IsPointIn(x, y))
		return this;

	return NULL;
}


cgUIWidgetPtr cgUIWidget::PickInChildren( int x, int y )
{
	cgUIWidgetPtrList::reverse_iterator it = m_kChildren.rbegin();
	for ( ; it != m_kChildren.rend(); ++it)
	{
		cgUIWidgetPtr& spChild = *it;
		if (!spChild || !spChild->IsVisible())
			continue;

		cgUIWidgetPtr spMouseComponent = spChild->Pick(x, y);
		if (spMouseComponent)
			return spMouseComponent;
	}

	return NULL;
}


bool cgUIWidget::IsPointIn( int x, int y )
{
	return (x>=m_kRect.x)&&(y>=m_kRect.y)
		&&(x<=(m_kRect.x+m_kRect.w))&&(y<=(m_kRect.y+m_kRect.h));
}

bool cgUIWidget::IsPointIn( const cgPoint& point )
{
	return IsPointIn(point.x, point.y);
}
// -------------------------------------------------------------------------------------


bool cgUIWidget::OnCopy()
{
	return false;
}

bool cgUIWidget::OnCut()
{
	return false;
}

bool cgUIWidget::OnPaste()
{
	return false;
}
// -------------------------------------------------------------------------------------


bool cgUIWidget::ReportDirty()
{
	// 父窗口为空的时候，说明没有加入UI树，不做绘制
	if (m_pkParent)
		cgUIManager::Get()->AddDirtyRect(m_kRect);

	return false;
}

void cgUIWidget::ReportUIEvent( cgUIEvent enmEvent )
{
	// 父窗口为空的时候，说明没有加入UI树，不做绘制
	if (m_pkParent)
		cgUIManager::Get()->OnUIEvent(this, enmEvent, 0, 0);
}

void cgUIWidget::OnTextChanged()
{

}

void cgUIWidget::OnFontChanged()
{

}

void cgUIWidget::OnTextStyleChanged()
{

}

void cgUIWidget::OnTextColorChanged()
{

}

void cgUIWidget::OnTextRowSpaceChanged()
{

}





