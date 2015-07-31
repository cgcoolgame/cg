#ifndef CGDefine_h__
#define CGDefine_h__

#include "cgStringDef.h"

#ifdef WIN32
	#include <Windows.h>
	#include <tchar.h>
	#include <assert.h>
#endif

#ifndef NULL
	#define NULL 0
#endif

// ----------------------------------------------------------------------------------------


// 颜色
typedef unsigned cgColor;

// ----------------------------------------------------------------------------------------

// 矩形
template<typename T>
struct cgRectT
{
	T x, y, w, h;

	cgRectT():
	x(static_cast<T>(0)), y(static_cast<T>(0)), 
		w(static_cast<T>(0)), h(static_cast<T>(0)){}

	cgRectT(T xPos, T yPos, T width, T height):
	x(xPos), y(yPos), w(width), h(height){};

	T GetLeft()const{return x;}
	T GetRight()const{return x+w;}
	T GetTop()const{return y;}
	T GetBottom()const{return y+h;}

	cgRectT& Set(T xPos, T yPos, T width, T height)
	{
		x = xPos; y = yPos; w = width; h = height;
		return *this;
	}
};

typedef cgRectT<int> cgRect;
typedef cgRectT<float> cgRectF;

// ----------------------------------------------------------------------------------------

// 点,仅适用于屏幕点
template<typename T>
struct cgPointT
{
	T x, y;

	cgPointT():
	x(static_cast<T>(0)), y(static_cast<T>(0)){}

	cgPointT(T xPos, T yPos):
	x(xPos), y(yPos){}

	cgPointT& Set(T xPos, T yPos)
	{
		x = xPos; y = yPos;
		return *this;
	}
};

typedef cgPointT<int> cgPoint;
typedef cgPointT<float> cgPointF;
// ----------------------------------------------------------------------------------------
// 尺寸
template<typename T>
struct cgSizeT
{
	T w, h;

	cgSizeT():
	w(static_cast<T>(0)), h(static_cast<T>(0)){}

	cgSizeT(T width, T height):
	w(width), h(height){}

	cgSizeT & Set(T width, T height)
	{
		w = width; h = height;
		return *this;
	}
};

typedef cgSizeT<unsigned> cgSize;
typedef cgSizeT<float> cgSizeF;
// ----------------------------------------------------------------------------------------

// 2D绘制顶点
typedef struct tagRenderVertex2D
{
	// 坐标
	float x;
	float y;

	// 纹理坐标
	float u;
	float v;

	// 颜色
	cgColor color;
}cgRenderVertex;


// ----------------------------------------------------------------------------------------
// 窗口句柄
typedef HWND cgHwnd;

enum cgWindowCreateFlag
{
	cgWindowCreateFlag_Default = 0,
	cgWindowCreateFlag_Layered = 1,		// 就是gdiplus用到的layered window
//	cgWindowCreateFlag_Child = 2,		// 无标题框，无边框
};

// ----------------------------------------------------------------------------------------
// id
typedef unsigned cgID;

const cgID CG_INVALID_ID = -1;

// 字体的一些定义
typedef struct tagFontConfig
{
	unsigned uSize;
	unsigned uHeight;
	unsigned uWidth;
	unsigned uWeight;
	unsigned uMipLevels;
	unsigned uItalic;
	unsigned uCharSet;
	unsigned uOutputPrecision;
	unsigned uClipPrecision;
	unsigned uQuality;
	unsigned uPitchAndFamily;
	TCHAR szFaceName[CG_SHORT_TEXT_BUFF_LEN];

	// 下面是由于美术字的
	TCHAR szText[CG_LONG_TEXT_BUFF_LEN];
	TCHAR szPicPath[CG_MAX_IMAGE_PATH_LEN];

}cgFontConfig;


// ----------------------------------------------------------------------------------------
// 截图格式
enum cgScreenShotImageFormat
{
	cgScreenShotImageFormat_BMP         = 0,
	cgScreenShotImageFormat_JPG         = 1,
	cgScreenShotImageFormat_TGA         = 2,
	cgScreenShotImageFormat_PNG         = 3,
	cgScreenShotImageFormat_DDS         = 4,
	cgScreenShotImageFormat_PPM         = 5,
	cgScreenShotImageFormat_DIB         = 6,
	cgScreenShotImageFormat_HDR         = 7,       //high dynamic range formats
	cgScreenShotImageFormat_PFM         = 8,       //
};


#include "cgVector.h"
#endif // CGDefine_h__
