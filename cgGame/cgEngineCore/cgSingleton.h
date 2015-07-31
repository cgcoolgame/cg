////////////////////////////////////////////////
//     FileName:    dxsingleton.h
//     Author:      Fish
//     Date:        2007-2-9 11:02:41
//     Description: 简单易用的单件实现基类(要求类的构造函数支持无参数类型)
////////////////////////////////////////////////
#ifndef _CG_SINGLETON_H_
#define _CG_SINGLETON_H_

template<class T>
class cgSingleton
{
public:
	//##取得单件实例
	static T* Instance()
	{
		return ms_pObject;
	}

	//##//##取得单件实例的另一方式
	static T* Get()
	{
		return ms_pObject;
	}
	//创建单件
	static T* Create()
	{
		if ( !ms_pObject )
		{
			ms_pObject = new T;
		}
		return ms_pObject;
	}

	//销毁单件
	static void Destroy()
	{
		if ( ms_pObject )
		{
			delete ms_pObject;
			ms_pObject = NULL;
		}
	}

protected:
	static T* ms_pObject;
};

template<class T> 
T* cgSingleton<T>::ms_pObject = NULL;

#endif