#ifndef cgUIDef_h__
#define cgUIDef_h__

// msg是收到的各种消息
typedef UINT cgUIMsg;

#define cgUIMsg_MouseIn	(WM_USER+1)
#define cgUIMsg_MouseOut	(WM_USER+2)
#define cgUIMsg_GainFocus	(WM_USER+3)
#define cgUIMsg_LostFocus	(WM_USER+4)

#define cgUIMsg_Copy	(WM_USER+101)
#define cgUIMsg_Cut	(WM_USER+102)
#define cgUIMsg_Paste	(WM_USER+103)


// -------------------------------------------------------------------------------------
// event是触发的各种事件
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
// 控件风格
// 比较稳定的叫style
//////////////////////////////////////////////////////////////////////////
enum cgUIStyle
{
	cgUIStyle_Static = 1,
	cgUIStyle_XMove = 1<<1,
	cgUIStyle_YMove = 1<<2,
};

//////////////////////////////////////////////////////////////////////////
// 控件状态
// 动态改变的为状态，比如是否可见，是否是hot
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
// 控件的一些状态，比如是否可见，是否是hot
// enble可以接收消息、可以吃掉消息，但是不产生响应
// static完全不接收消息，不吃掉消息，不响应，不可拾取，但是能看到
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
// cgUIRichText 的一些定义

// Ui字符的类型
//enum cgUICharType
//{
//	// 普通字符：ABC
//	cgUICharType_Char,
//
//	// 行结束：<endl>
//	cgUICharType_EndLine,
//
//	// 颜色控制字符: <color value=0xffffffff> ABC </color>
//	cgUICharType_ColorBegin,
//	cgUICharType_ColorEnd,
//
//	// 图片: <img path=./res/a.png>
//	cgUICharType_Image,
//
//	// 链接: <link type=http value=www.baidu.com> BAIDU </link>
//	cgUICharType_LinkBegin,
//	cgUICharType_LinkEnd,
//
//	// 字体: <font id=0> ABC </font>
//	cgUICharType_FontBegin,
//	cgUICharType_FontEnd,
//
//	// 下划线: <underline> ABC </underline>
//	cgUICharType_UnderLineBegin,
//	cgUICharType_UnderLineEnd,
//
//	// 删除线: <delline> ABC </delline>
//	cgUICharType_DelLineBegin,
//	cgUICharType_DelLineEnd,
//};

// 一个UI字符的原始字符串长度
#define CG_UI_CHAR_MAX_RAW_STRING_LEN	1024


// ---------------------------------------------------------------------------------------


#ifdef _DEBUG

#include <iostream>
using namespace std;
#endif

#endif // cgUIDef_h__
