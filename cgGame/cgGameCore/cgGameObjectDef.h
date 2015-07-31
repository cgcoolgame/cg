#ifndef cgGameObjectDef_h__
#define cgGameObjectDef_h__
#include <cgMath.h>

// �任
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

// ��������
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

// ��ȣ�����ͬһ���ڵ���ӽڵ�Ļ�����ȣ����ԽС��Խ�Ȼ���
static const cgGameObjectDepth cgGameObjectDepth_MIN = -cgMath::FLOAT_MAX;
static const cgGameObjectDepth cgGameObjectDepth_Zero = 0.0f;
static const cgGameObjectDepth cgGameObjectDepth_Defalut = cgMath::FLOAT_EPSILON;
static const cgGameObjectDepth cgGameObjectDepth_MAX = cgMath::FLOAT_MAX;

// ��layer��һ�㣬Ԥ����ļ������
static const cgGameObjectDepth cgGameObjectDepth_Background_Layer = cgGameObjectDepth_Zero;
static const cgGameObjectDepth cgGameObjectDepth_Scene_Layer = cgGameObjectDepth_Defalut;
static const cgGameObjectDepth cgGameObjectDepth_UI_Layer = cgGameObjectDepth_MAX-cgMath::FLOAT_EPSILON;
static const cgGameObjectDepth cgGameObjectDepth_TopMost_Layer = cgGameObjectDepth_MAX;

// ----------------------------------------------------------------------------------
// GameObjectEvent
// 0-999 �������ڲ�ʹ�õģ���Ҫ�޸�
// �����Ϸ�߼��Զ���ģ������1000������cgGameObjectEvent_CustomBegin
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

// ����������UI�ĵ�
// ��������Ϸ�߼��Զ���
static const cgGameObjectEvent cgGameObjectEvent_CustomBegin = 1000;
// ----------------------------------------------------------------------------------
#endif // cgGameObjectDef_h__

