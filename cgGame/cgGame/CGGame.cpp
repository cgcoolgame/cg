// cgGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "cgPickGame.h"
#include "cgTetris.h"
#include "cgILoveShooting.h"
#include "cgRunApp.h"
#include "cgUITest.h"
#include "cgGdiplusUITest.h"
#include "cgWebGame.h"

#ifdef _DEBUG
#define _USE_CONSOLE_
#endif


// 启动游戏模板,默认参数的
template<typename T>
void cgRunGame(int w, int h)
{
	if (T::Create()->Initialize(w, h))
	{
		T::Get()->Run();
	}
	T::Destroy();
}

// 启动游戏模板，全参数的
template<typename T>
void cgRunGame(int w, int h, int style, int extendStyle)
{
	if (T::Create()->Initialize(w, h, style, extendStyle))
	{
		T::Get()->Run();
	}
	T::Destroy();
}

#ifdef _USE_CONSOLE_

	#include <iostream>
	using namespace std;

int main()
{	

#else

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
#endif

	int appIndex = 5;
	switch (appIndex)
	{
	case 0:
		{
			cgRunGame<cgPickGame>(1024, 768);
		}break;
	case 1:
		{
			cgRunGame<cgTetris>(1024, 768);
		}break;
	case 2:
		{
			cgRunGame<cgILoveShooting>(1024, 768);
		}break;
	case 3:
		{
			cgRunGame<cgRunApp>(1024, 768);
		}break;
	case 4:
		{
			cgRunGame<cgUITest>(1024, 768);
		}break;
	case 5:
		{
			cgRunGame<cgGdiplusUITest>(1024, 768);
		}break;
	case 6:
		{
			// 右下角流氓弹窗，需要最顶层（WS_EX_TOPMOST），且不在任务栏显示（WS_EX_TOOLWINDOW）
			cgRunGame<cgWebGame>(320, 240, WS_POPUP, WS_EX_TOPMOST|WS_EX_LAYERED|WS_EX_TOOLWINDOW);
		}break;

	default:
		break;
	}
	
#ifdef _DEBUG
	unsigned uNum = cgRefObject::GetTotalObjectNum();
	cout<<"cgRefObject::GetTotalObjectNum():"<<uNum<<endl;
	cout<<"cgRefObject::GetTotalIncrease():"<<cgRefObject::GetTotalIncrease()<<endl;
	cout<<"cgRefObject::GetTotalDecrease():"<<cgRefObject::GetTotalDecrease()<<endl;
#endif
	
//	system("pause");

	return 0;
}
