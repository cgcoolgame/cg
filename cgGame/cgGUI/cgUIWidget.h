#ifndef cgUIWidget_h__
#define cgUIWidget_h__

#include <vector>
#include "cgUIDef.h"
#include "cgSmartPointer.h"
#include "cgUIImage.h"
#include "cgRefObject.h"

class cgUIRender;
class cgUIWidget;

typedef cgSmartPointer<cgUIWidget> cgUIWidgetPtr;
typedef std::vector<cgUIWidgetPtr> cgUIWidgetPtrList;

class cgUIWidget:public cgRefObject
{
public:
	cgUIWidget(void);
	cgUIWidget(const string& strName);

	virtual ~cgUIWidget(void);

public:
	// UI消息
	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

	// 更新
	virtual void Update(float fTime);

	// 绘制，渲染
	virtual void Render(const cgRectF& dirtyRect);

	// 添加子控件
	virtual void AddChild(cgUIWidgetPtr spChild);

	// 获取子控件个数
	unsigned GetChildNum();

	// 删除一个孩子
	virtual void DelChild(cgUIWidgetPtr spChild);

	// 设置自身父控件
	void SetParent(cgUIWidget* pkParent);

	// 获得父控件
	cgUIWidget* GetParent();

// ------------------------------------------------------------------------------
	// 是否可见
	bool IsVisible()const;
	virtual void SetVisible(bool bVisible);

	// 是否焦点
	bool IsFocus()const;
	virtual void SetFocus(bool bFocus);

	// 是否hot
	bool IsMouseOver()const;
	virtual void SetMouseOver(bool bOver);

	// 是否点击
	bool IsClickDown()const;
	virtual void SetClickDown(bool bClick);

	// 是否可用
	bool IsEnable()const;
	virtual void SetEnable(bool bEnable);

	// 子控件是否有深度变化
	bool IsChildrenDepthDirty()const;
	virtual void SetChildrenDepthDirty(bool bDirty);

	// 最后设置最终状态
	int GetState()const;
	void SetState(int nState);
// ------------------------------------------------------------------------------

	// 是否静态
	bool IsStatic()const;
	virtual void SetStatic(bool bStatic);

	bool IsXMove();
	void SetXMove(bool bMove);

	bool IsYMove();
	void SetYMove(bool bMove);

	bool IsMovable();
	void SetMovable(bool bMove);

	int GetStyle()const;
	void SetStyle(int nStyle);
// ------------------------------------------------------------------------------

	// 是否自动缩放
	bool IsAutoScale()const;
	virtual void SetAutoScale(bool bAuto);

	// 是否绘制背景颜色
	bool IfFillBackground()const;
	virtual void SetDrawBackColor(bool bFill);

	// 是否绘制边框
	bool IfDrawBorder()const;
	virtual void SetDrawBorder(bool bDraw);

	// 是否剪切自身
	bool IfClipSelf()const;
	virtual void SetClipSelf(bool bClip);

	// 是否剪切子控件
	bool IfClipChildren()const;
	virtual void SetClipChildren(bool bClip);

	int GetDrawFlag()const;
	void SetDrawFlag(int nFlag);
// ------------------------------------------------------------------------------

	// 额外属性
	int GetExtendStyle()const;
	void SetExtendStyle(int nExtendStyle);
// ------------------------------------------------------------------------------
	// 设置位置和大小
	virtual void SetRect(int x, int y, int w, int h);
	virtual void SetPosition(int x, int y);
	virtual void SetSize(int w, int h);

	// 设置本地位置
	void SetLocalRect(int x, int y, int w, int h);
	void SetLocalPosition(int x, int y);

	const cgRectF& GetLocalRect();
	cgPointF GetLocalPosition();

	// 获取各种位置和大小
	int GetX()const;
	int GetY()const;
	int GetWidth()const;
	int GetHeight()const;

	// 移动
	virtual void Move(int x, int y);

	// 稍微封装一下
	virtual void SetRect(const cgRectF & rect);
	cgRectF GetRect()const;

	virtual void SetPosition(const cgPoint & point);
	cgPoint GetPosition()const;

	virtual void SetSize(const cgSize& size);
	cgSize GetSize()const;

	void SetDepth(int depth);
	int GetDepth()const;
// ------------------------------------------------------------------------------

	// 设置背景图片
	virtual void SetBackPic(LPCTSTR path);
	virtual void SetBackPic(cgID resID);

	// 设置文字
	virtual void SetText(LPCTSTR text);
	virtual LPCTSTR GetText()const;

	// 设置默认字体
	void SetFont(cgID id);
	cgID GetFont()const;

	// 设置对齐方式
	void SetTextStyle(int nStyle);
	int GetTextStyle()const;

	void SetTextRowSpace(int nSpace);
	int GetTextRowSpace()const;

	// 设置默认文字绘制颜色
	void SetTextColor(cgColor color);
	cgColor GetTextColor()const;

	void SetBackColor(cgColor color);
	cgColor GetBackColor()const;

	void SetBorderColor(cgColor color);
	cgColor GetBorderColor()const;
// ------------------------------------------------------------------------------
	// 设置标识
	void SetName(const string & strID);
	const string& GetName();

	void SetCursor(const string & strCursor);
	const string& GetCursor();

	// 获取路径
	void GetPath(string & path);

// ------------------------------------------------------------------------------

	// 自定义数据
	void SetCustomType(int nType);
	int GetCustomType()const;

	void SetCustomValue(int nValue);
	int GetCustomValue()const;

	void SetCustomString(const cgString& str);
	const cgString & GetCustomString()const;

// ------------------------------------------------------------------------------

	// 找控件，包含自己
	cgUIWidgetPtr FindComponent(const char * path);
	
	// 找子控件，不包含自己
	cgUIWidgetPtr FindChild(const char * path);

	// 查找鼠标悬停的有效控件
	cgUIWidgetPtr Pick(int x, int y);

	// 判断坐标是否在控件的范围内
	bool IsPointIn(int x, int y);
	bool IsPointIn(const cgPoint& point);

// ------------------------------------------------------------------------------
protected:

	// 设置参数
	void SetupParams();

	// 在子控件中查找
	cgUIWidgetPtr PickInChildren(int x, int y);

	// 更新自身
	virtual void UpdateSelf(float fTime);

	// 更新子控件
	virtual void UpdateChildren(float fTime);

	// 根据深度排序
	void SortChildrenByDepth();

	// 绘制自身
	virtual void RenderSelf(const cgRectF& dirtyRect);
	// 绘制子控件
	virtual void RenderChildren(const cgRectF& dirtyRect);

	virtual void DrawBorder(const cgRectF& clipRect);
	// 绘制背景色
	virtual void DrawBackground(const cgRectF& clipRect);

	// 绘制背景图片
	virtual void DrawBackPic(const cgRectF& clipRect);

	//************************************
	// Method:    DoDrawPic
	// FullName:  cgUIComponent::DoDrawPic
	// Access:    protected
	// Returns:   bool
	// Qualifier:
	// Parameter: cgUIImagePtr spPic ， 要绘制的图片
	// Parameter: const cgRect & boundRect，容纳该图片的矩形，一般都会有各种对齐方式
	// Parameter: const cgRect & clipRect，剪切
	//************************************
	bool DoDrawPic(cgUIImagePtr spPic, const cgRectF& boundRect, const cgRectF& clipRect);

	// 绘制文字
	virtual void DrawText(const cgRectF& clipRect);

	// 触发事件
	virtual void ReportUIEvent(cgUIEvent enmEvent);

	// ctrl+c
	bool OnCopy();

	// ctrl+x
	bool OnCut();

	// ctrl+v
	bool OnPaste();

	// 报告自己需要重绘
	virtual bool ReportDirty();

	// 父节点移动了，那么自己也要做相应的移动
	void MoveSelf(int x, int y);
	void MoveChildren();
	void OnParentMoved();

	virtual void OnPositionChanged();
	virtual void OnSizeChanged();

	// 文本相关
	virtual void OnTextChanged();
	virtual void OnFontChanged();
	virtual void OnTextStyleChanged();
	virtual void OnTextColorChanged();
	virtual void OnTextRowSpaceChanged();
	
protected:
	cgRectF m_kRect;
	cgRectF m_kLocalRect;
	int m_nDepth;

	int m_nStyle;
	int m_nDrawFlag;
	int m_nState;
	int m_nExtendStyle;	// 额外属性，和具体控件相关的

	string m_strName;
	string m_strCursor;

	cgUIImagePtr m_spBkImage;

	cgString m_strText;
	cgID m_idFont;
	int m_nTextStyle;
	int m_nTextRowSpace;

	cgColor m_uTextColor;	// 字体颜色
	cgColor m_uBackColor;	// 背景颜色
	cgColor m_uBorderColor; // 边框颜色

	int m_nCustomType;
	int m_nCustomValue;
	cgString m_strCustomString;

	cgUIWidget* m_pkParent;

	cgUIWidgetPtrList m_kChildren;

	// 鼠标在UI内点击时，ui和鼠标位置的距离：dis = pos-mouse
	// 当mouse拖动了ui时，利用这个距离可以算出新的UI位置：pos = mouse+dis
	cgPoint m_kDistanceToMouseDown;
};

#endif // cgUIWidget_h__
