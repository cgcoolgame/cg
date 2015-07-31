#ifndef CGDefine_h__
#define CGDefine_h__

#ifdef WIN32

#include <Windows.h>
#include <tchar.h>
#include <assert.h>
#include <string>

#endif

#ifndef NULL
#define NULL 0
#endif

#define CG_MAX_IMAGE_PATH_LEN 256
#define CG_SHORT_TEXT_BUFF_LEN	 64
#define CG_NORMAL_TEXT_BUFF_LEN 256
#define CG_LONG_TEXT_BUFF_LEN	512
#define CG_LONG_LONG_TEXT_BUFF_LEN 1024

#define  cgStrLen _tcsclen

#ifdef UNICODE
	#define	cgSprintf swprintf_s
	typedef	std::wstring cgString;
#else
	#define	cgSprintf sprintf_s
	typedef	std::string cgString;
#endif

using std::string;

// 矩形
struct cgRect
{
	cgRect()
	{
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
	}
	cgRect(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	int x;
	int y;
	int w;
	int h;
};

// 点
struct cgPoint
{
	cgPoint()
	{
		x = 0;
		y = 0;
	}
	cgPoint(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
};

// 尺寸
struct cgSize
{
	cgSize()
	{
		w = h = 0;
	}
	cgSize(int w, int h)
	{
		this->w = w;
		this->h = h;
	}
	unsigned int w;
	unsigned int h;
};

// 颜色
typedef unsigned cgColor;

// 窗口句柄
typedef HWND cgWindowHandle;

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


#endif // CGDefine_h__
