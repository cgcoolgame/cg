// HelloWorld.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
template<typename T>
T TMax(T l, T r)
{
	return l > r?l:r;
}
#else
#define TMax(a,b) ((a)>(b)?(a):(b))
#endif


int _tmain(int argc, _TCHAR* argv[])
{
	int nFind = 0;
	for (int i = 0; i < 100; ++i)
	{
		cout<<"Hello World !"<<endl;

		nFind = TMax(nFind, rand());
		cout<<"Temp Max = "<<nFind<<endl;
	}
	
	cout<<"Max = "<<nFind<<endl;

	system("pause");

	return 0;
}

