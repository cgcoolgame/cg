#ifndef cgGameObjectDef_h__
#define cgGameObjectDef_h__
#include <cgMath.h>

// 变换
struct cgTransform
{
	cgVector pos;			
	cgVector scale;
	float rotation;

	cgTransform()
		:pos(0.0f, 0.0f), 
		scale(1.0f, 1.0f),
		rotation(0.0f){}
};

// 绘制属性
struct cgRenderProps
{
	cgColor color;
	float alpha;

	cgRenderProps()
		:color(0xffffffff),
		alpha(1.0f){}
};
// ----------------------------------------------------------------------------------
typedef float cgGameObjectDepth;

// 深度，所有同一父节点的子节点的绘制深度，深度越小，越先绘制
static const cgGameObjectDepth cgGameObjectDepth_MIN = -cgMath::FLOAT_MAX;
static const cgGameObjectDepth cgGameObjectDepth_Zero = 0.0f;
static const cgGameObjectDepth cgGameObjectDepth_Defalut = cgMath::FLOAT_EPSILON;
static const cgGameObjectDepth cgGameObjectDepth_MAX = cgMath::FLOAT_MAX;

// 在layer这一层，预定义的几个深度
static const cgGameObjectDepth cgGameObjectDepth_Background_Layer = cgGameObjectDepth_Zero;
static const cgGameObjectDepth cgGameObjectDepth_Scene_Layer = cgGameObjectDepth_Defalut;
static const cgGameObjectDepth cgGameObjectDepth_UI_Layer = cgGameObjectDepth_MAX-cgMath::FLOAT_EPSILON;
static const cgGameObjectDepth cgGameObjectDepth_TopMost_Layer = cgGameObjectDepth_MAX;

// ----------------------------------------------------------------------------------
// GameObjectEvent
// 0-999 是引擎内部使用的，不要修改
// 如果游戏逻辑自定义的，请大于1000，即：cgGameObjectEvent_CustomBegin
typedef int cgGameObjectEvent;

static const cgGameObjectEvent cgGameObjectEvent_Begin = 0;
static const cgGameObjectEvent cgGameObjectEvent_MouseEnter = 0;
static const cgGameObjectEvent cgGameObjectEvent_MouseOut = 1;
static const cgGameObjectEvent cgGameObjectEvent_MouseDown = 2;
static const cgGameObjectEvent cgGameObjectEvent_MouseUp = 3;
static const cgGameObjectEvent cgGameObjectEvent_MouseMove =4;
static const cgGameObjectEvent cgGameObjectEvent_MouseWheel =5;
static const cgGameObjectEvent cgGameObjectEvent_DBClick = 6;
static const cgGameObjectEvent cgGameObjectEvent_GainFocus = 7;
static const cgGameObjectEvent cgGameObjectEvent_LostFocus = 8;
static const cgGameObjectEvent cgGameObjectEvent_InputChar = 9;
static const cgGameObjectEvent cgGameObjectEvent_Copy = 10;
static const cgGameObjectEvent cgGameObjectEvent_Cut = 11;
static const cgGameObjectEvent cgGameObjectEvent_Paste = 12;

// 上面适用于UI的的
// 下面是游戏逻辑自定义
static const cgGameObjectEvent cgGameObjectEvent_CustomBegin = 1000;
// ----------------------------------------------------------------------------------
#endif // cgGameObjectDef_h__

