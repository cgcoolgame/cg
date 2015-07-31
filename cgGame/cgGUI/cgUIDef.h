#ifndef cgUIDef_h__
#define cgUIDef_h__

// msg���յ��ĸ�����Ϣ
typedef UINT cgUIMsg;

#define cgUIMsg_MouseIn	(WM_USER+1)
#define cgUIMsg_MouseOut	(WM_USER+2)
#define cgUIMsg_GainFocus	(WM_USER+3)
#define cgUIMsg_LostFocus	(WM_USER+4)

#define cgUIMsg_Copy	(WM_USER+101)
#define cgUIMsg_Cut	(WM_USER+102)
#define cgUIMsg_Paste	(WM_USER+103)


// -------------------------------------------------------------------------------------
// event�Ǵ����ĸ����¼�
enum cgUIEvent
{
	cgUIEvent_OnMouseIn = 0,
	cgUIEvent_OnMouseOut = 1,
	cgUIEvent_OnGainFocus = 2,
	cgUIEvent_OnLostFocus = 3,
	cgUIEvent_OnEnter = 4,
	cgUIEvent_OnTab = 5,
	cgUIEvent_OnClick = 6,
	cgUIEvent_OnRClick = 7,
	cgUIEvent_OnDbClick = 8,
	cgUIEvent_OnSizeChange = 9,
	cgUIEvent_OnMove = 10,
	cgUIEvent_OnTextChange = 11,
	cgUIEvent_OnScreenChanged ,
};

static const char * cgUIEventName[]=
{
	"OnMouseIn",
	"OnMouseOut",
	"OnGainFocus",
	"OnLostFocus",
	"OnEnter",
	"OnTab",
	"OnClick",
	"OnRClick",
	"OnDbClick",
	"OnSizeChange",
	"OnMove",
	"OnTextChange",
	"OnScreenChanged",
};

// -------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
// �ؼ����
// �Ƚ��ȶ��Ľ�style
//////////////////////////////////////////////////////////////////////////
enum cgUIStyle
{
	cgUIStyle_Static = 1,
	cgUIStyle_XMove = 1<<1,
	cgUIStyle_YMove = 1<<2,
};

//////////////////////////////////////////////////////////////////////////
// �ؼ�״̬
// ��̬�ı��Ϊ״̬�������Ƿ�ɼ����Ƿ���hot
//////////////////////////////////////////////////////////////////////////
enum cgUIState
{
	cgUIState_Visible = 1,
	cgUIState_Focus = 1<<1,
	cgUIState_MouseOver = 1<<2,
	cgUIState_ClickDown = 1<<3,
	cgUIState_Enable = 1<<4,
	cgUIState_DepthDirty = 1<<5,
};

//////////////////////////////////////////////////////////////////////////
// �ؼ���һЩ״̬�������Ƿ�ɼ����Ƿ���hot
// enble���Խ�����Ϣ�����ԳԵ���Ϣ�����ǲ�������Ӧ
// static��ȫ��������Ϣ�����Ե���Ϣ������Ӧ������ʰȡ�������ܿ���
//////////////////////////////////////////////////////////////////////////
enum cgUIDrawFlag
{
	cgUIDrawFlag_AutoScale = 1,
	cgUIDrawFlag_DrawBackColor = 1<<1,
	cgUIDrawFlag_DrawBorder = 1<<2,
	cgUIDrawFlag_ClipSelf = 1<<3,
	cgUIDrawFlag_ClipChildren = 1<<4,
};
// -------------------------------------------------------------------------------------
enum cgButtonExtendStyle
{
	
};


// -------------------------------------------------------------------------------------
enum cgProgressBarExtendStyle
{
	cgProgressBarExtendStyle_Immediate = 1,
	cgProgressBarExtendStyle_Vertical  = 1<<1,
};

// -------------------------------------------------------------------------------------
enum enmUIEditType
{
	enmUIEditType_Normal = 0,
	enmUIEditType_Password = 1,
};
// -------------------------------------------------------------------------------------
// cgUIRichText ��һЩ����

// Ui�ַ�������
//enum cgUICharType
//{
//	// ��ͨ�ַ���ABC
//	cgUICharType_Char,
//
//	// �н�����<endl>
//	cgUICharType_EndLine,
//
//	// ��ɫ�����ַ�: <color value=0xffffffff> ABC </color>
//	cgUICharType_ColorBegin,
//	cgUICharType_ColorEnd,
//
//	// ͼƬ: <img path=./res/a.png>
//	cgUICharType_Image,
//
//	// ����: <link type=http value=www.baidu.com> BAIDU </link>
//	cgUICharType_LinkBegin,
//	cgUICharType_LinkEnd,
//
//	// ����: <font id=0> ABC </font>
//	cgUICharType_FontBegin,
//	cgUICharType_FontEnd,
//
//	// �»���: <underline> ABC </underline>
//	cgUICharType_UnderLineBegin,
//	cgUICharType_UnderLineEnd,
//
//	// ɾ����: <delline> ABC </delline>
//	cgUICharType_DelLineBegin,
//	cgUICharType_DelLineEnd,
//};

// һ��UI�ַ���ԭʼ�ַ�������
#define CG_UI_CHAR_MAX_RAW_STRING_LEN	1024


// ---------------------------------------------------------------------------------------


#ifdef _DEBUG

#include <iostream>
using namespace std;
#endif

#endif // cgUIDef_h__
