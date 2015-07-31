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
	// UI��Ϣ
	virtual bool OnMessage(cgUIMsg msg, unsigned wparam, unsigned lparam);

	// ����
	virtual void Update(float fTime);

	// ���ƣ���Ⱦ
	virtual void Render(const cgRectF& dirtyRect);

	// ����ӿؼ�
	virtual void AddChild(cgUIWidgetPtr spChild);

	// ��ȡ�ӿؼ�����
	unsigned GetChildNum();

	// ɾ��һ������
	virtual void DelChild(cgUIWidgetPtr spChild);

	// ���������ؼ�
	void SetParent(cgUIWidget* pkParent);

	// ��ø��ؼ�
	cgUIWidget* GetParent();

// ------------------------------------------------------------------------------
	// �Ƿ�ɼ�
	bool IsVisible()const;
	virtual void SetVisible(bool bVisible);

	// �Ƿ񽹵�
	bool IsFocus()const;
	virtual void SetFocus(bool bFocus);

	// �Ƿ�hot
	bool IsMouseOver()const;
	virtual void SetMouseOver(bool bOver);

	// �Ƿ���
	bool IsClickDown()const;
	virtual void SetClickDown(bool bClick);

	// �Ƿ����
	bool IsEnable()const;
	virtual void SetEnable(bool bEnable);

	// �ӿؼ��Ƿ�����ȱ仯
	bool IsChildrenDepthDirty()const;
	virtual void SetChildrenDepthDirty(bool bDirty);

	// �����������״̬
	int GetState()const;
	void SetState(int nState);
// ------------------------------------------------------------------------------

	// �Ƿ�̬
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

	// �Ƿ��Զ�����
	bool IsAutoScale()const;
	virtual void SetAutoScale(bool bAuto);

	// �Ƿ���Ʊ�����ɫ
	bool IfFillBackground()const;
	virtual void SetDrawBackColor(bool bFill);

	// �Ƿ���Ʊ߿�
	bool IfDrawBorder()const;
	virtual void SetDrawBorder(bool bDraw);

	// �Ƿ��������
	bool IfClipSelf()const;
	virtual void SetClipSelf(bool bClip);

	// �Ƿ�����ӿؼ�
	bool IfClipChildren()const;
	virtual void SetClipChildren(bool bClip);

	int GetDrawFlag()const;
	void SetDrawFlag(int nFlag);
// ------------------------------------------------------------------------------

	// ��������
	int GetExtendStyle()const;
	void SetExtendStyle(int nExtendStyle);
// ------------------------------------------------------------------------------
	// ����λ�úʹ�С
	virtual void SetRect(int x, int y, int w, int h);
	virtual void SetPosition(int x, int y);
	virtual void SetSize(int w, int h);

	// ���ñ���λ��
	void SetLocalRect(int x, int y, int w, int h);
	void SetLocalPosition(int x, int y);

	const cgRectF& GetLocalRect();
	cgPointF GetLocalPosition();

	// ��ȡ����λ�úʹ�С
	int GetX()const;
	int GetY()const;
	int GetWidth()const;
	int GetHeight()const;

	// �ƶ�
	virtual void Move(int x, int y);

	// ��΢��װһ��
	virtual void SetRect(const cgRectF & rect);
	cgRectF GetRect()const;

	virtual void SetPosition(const cgPoint & point);
	cgPoint GetPosition()const;

	virtual void SetSize(const cgSize& size);
	cgSize GetSize()const;

	void SetDepth(int depth);
	int GetDepth()const;
// ------------------------------------------------------------------------------

	// ���ñ���ͼƬ
	virtual void SetBackPic(LPCTSTR path);
	virtual void SetBackPic(cgID resID);

	// ��������
	virtual void SetText(LPCTSTR text);
	virtual LPCTSTR GetText()const;

	// ����Ĭ������
	void SetFont(cgID id);
	cgID GetFont()const;

	// ���ö��뷽ʽ
	void SetTextStyle(int nStyle);
	int GetTextStyle()const;

	void SetTextRowSpace(int nSpace);
	int GetTextRowSpace()const;

	// ����Ĭ�����ֻ�����ɫ
	void SetTextColor(cgColor color);
	cgColor GetTextColor()const;

	void SetBackColor(cgColor color);
	cgColor GetBackColor()const;

	void SetBorderColor(cgColor color);
	cgColor GetBorderColor()const;
// ------------------------------------------------------------------------------
	// ���ñ�ʶ
	void SetName(const string & strID);
	const string& GetName();

	void SetCursor(const string & strCursor);
	const string& GetCursor();

	// ��ȡ·��
	void GetPath(string & path);

// ------------------------------------------------------------------------------

	// �Զ�������
	void SetCustomType(int nType);
	int GetCustomType()const;

	void SetCustomValue(int nValue);
	int GetCustomValue()const;

	void SetCustomString(const cgString& str);
	const cgString & GetCustomString()const;

// ------------------------------------------------------------------------------

	// �ҿؼ��������Լ�
	cgUIWidgetPtr FindComponent(const char * path);
	
	// ���ӿؼ����������Լ�
	cgUIWidgetPtr FindChild(const char * path);

	// ���������ͣ����Ч�ؼ�
	cgUIWidgetPtr Pick(int x, int y);

	// �ж������Ƿ��ڿؼ��ķ�Χ��
	bool IsPointIn(int x, int y);
	bool IsPointIn(const cgPoint& point);

// ------------------------------------------------------------------------------
protected:

	// ���ò���
	void SetupParams();

	// ���ӿؼ��в���
	cgUIWidgetPtr PickInChildren(int x, int y);

	// ��������
	virtual void UpdateSelf(float fTime);

	// �����ӿؼ�
	virtual void UpdateChildren(float fTime);

	// �����������
	void SortChildrenByDepth();

	// ��������
	virtual void RenderSelf(const cgRectF& dirtyRect);
	// �����ӿؼ�
	virtual void RenderChildren(const cgRectF& dirtyRect);

	virtual void DrawBorder(const cgRectF& clipRect);
	// ���Ʊ���ɫ
	virtual void DrawBackground(const cgRectF& clipRect);

	// ���Ʊ���ͼƬ
	virtual void DrawBackPic(const cgRectF& clipRect);

	//************************************
	// Method:    DoDrawPic
	// FullName:  cgUIComponent::DoDrawPic
	// Access:    protected
	// Returns:   bool
	// Qualifier:
	// Parameter: cgUIImagePtr spPic �� Ҫ���Ƶ�ͼƬ
	// Parameter: const cgRect & boundRect�����ɸ�ͼƬ�ľ��Σ�һ�㶼���и��ֶ��뷽ʽ
	// Parameter: const cgRect & clipRect������
	//************************************
	bool DoDrawPic(cgUIImagePtr spPic, const cgRectF& boundRect, const cgRectF& clipRect);

	// ��������
	virtual void DrawText(const cgRectF& clipRect);

	// �����¼�
	virtual void ReportUIEvent(cgUIEvent enmEvent);

	// ctrl+c
	bool OnCopy();

	// ctrl+x
	bool OnCut();

	// ctrl+v
	bool OnPaste();

	// �����Լ���Ҫ�ػ�
	virtual bool ReportDirty();

	// ���ڵ��ƶ��ˣ���ô�Լ�ҲҪ����Ӧ���ƶ�
	void MoveSelf(int x, int y);
	void MoveChildren();
	void OnParentMoved();

	virtual void OnPositionChanged();
	virtual void OnSizeChanged();

	// �ı����
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
	int m_nExtendStyle;	// �������ԣ��;���ؼ���ص�

	string m_strName;
	string m_strCursor;

	cgUIImagePtr m_spBkImage;

	cgString m_strText;
	cgID m_idFont;
	int m_nTextStyle;
	int m_nTextRowSpace;

	cgColor m_uTextColor;	// ������ɫ
	cgColor m_uBackColor;	// ������ɫ
	cgColor m_uBorderColor; // �߿���ɫ

	int m_nCustomType;
	int m_nCustomValue;
	cgString m_strCustomString;

	cgUIWidget* m_pkParent;

	cgUIWidgetPtrList m_kChildren;

	// �����UI�ڵ��ʱ��ui�����λ�õľ��룺dis = pos-mouse
	// ��mouse�϶���uiʱ��������������������µ�UIλ�ã�pos = mouse+dis
	cgPoint m_kDistanceToMouseDown;
};

#endif // cgUIWidget_h__
