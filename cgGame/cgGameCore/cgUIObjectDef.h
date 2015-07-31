
#ifndef cgUIObjectDef_h__
#define cgUIObjectDef_h__

// ------------------------------------------------------------------
// ���Ʊ��
typedef unsigned cgUIObjectDrawFlag;
static const cgUIObjectDrawFlag cgUIObjectDrawFlag_DrawBackGround = 1;
static const cgUIObjectDrawFlag cgUIObjectDrawFlag_DrawBorder = 1<<1;
static const cgUIObjectDrawFlag cgUIObjectDrawFlag_AutoScale = 1<<2;
// ------------------------------------------------------------------
// UI���:�Ƚ��ȶ��Ľ�style
typedef unsigned cgUIObjectStyle;

static const cgUIObjectStyle cgUIObjectStyle_Static = 1;
static const cgUIObjectStyle cgUIObjectStyle_XMove = 1<<1;
static const cgUIObjectStyle cgUIObjectStyle_YMove = 1<<2;


// ------------------------------------------------------------------
// �����񣬾��岻ͬ�Ŀؼ��ǲ�ͬ��
typedef unsigned cgUIObjectExtendStyle;


// ------------------------------------------------------------------
// UI״̬����̬�ı��Ϊstate
typedef unsigned cgUIObjectState;

// Ԥ����״̬
static const cgUIObjectState cgUIObjectState_Visible = 1;
static const cgUIObjectState cgUIObjectState_Focus = 1<<1;
static const cgUIObjectState cgUIObjectState_MouseOver = 1<<2;
static const cgUIObjectState cgUIObjectState_MouseDown = 1<<3;


#endif // cgUIObjectDef_h__
