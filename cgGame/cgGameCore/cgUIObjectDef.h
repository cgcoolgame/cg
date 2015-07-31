
#ifndef cgUIObjectDef_h__
#define cgUIObjectDef_h__

// ------------------------------------------------------------------
// 绘制标记
typedef unsigned cgUIObjectDrawFlag;
static const cgUIObjectDrawFlag cgUIObjectDrawFlag_DrawBackGround = 1;
static const cgUIObjectDrawFlag cgUIObjectDrawFlag_DrawBorder = 1<<1;
static const cgUIObjectDrawFlag cgUIObjectDrawFlag_AutoScale = 1<<2;
// ------------------------------------------------------------------
// UI风格:比较稳定的叫style
typedef unsigned cgUIObjectStyle;

static const cgUIObjectStyle cgUIObjectStyle_Static = 1;
static const cgUIObjectStyle cgUIObjectStyle_XMove = 1<<1;
static const cgUIObjectStyle cgUIObjectStyle_YMove = 1<<2;


// ------------------------------------------------------------------
// 额外风格，具体不同的控件是不同的
typedef unsigned cgUIObjectExtendStyle;


// ------------------------------------------------------------------
// UI状态：动态改变的为state
typedef unsigned cgUIObjectState;

// 预定的状态
static const cgUIObjectState cgUIObjectState_Visible = 1;
static const cgUIObjectState cgUIObjectState_Focus = 1<<1;
static const cgUIObjectState cgUIObjectState_MouseOver = 1<<2;
static const cgUIObjectState cgUIObjectState_MouseDown = 1<<3;


#endif // cgUIObjectDef_h__
