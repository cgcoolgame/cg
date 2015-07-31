////////////////////////////////////////////////
//     FileName:    dxsingleton.h
//     Author:      Fish
//     Date:        2007-2-9 11:02:41
//     Description: �����õĵ���ʵ�ֻ���(Ҫ����Ĺ��캯��֧���޲�������)
////////////////////////////////////////////////
#ifndef _CG_SINGLETON_H_
#define _CG_SINGLETON_H_

template<class T>
class cgSingleton
{
public:
	//##ȡ�õ���ʵ��
	static T* Instance()
	{
		return ms_pObject;
	}

	//##//##ȡ�õ���ʵ������һ��ʽ
	static T* Get()
	{
		return ms_pObject;
	}
	//��������
	static T* Create()
	{
		if ( !ms_pObject )
		{
			ms_pObject = new T;
		}
		return ms_pObject;
	}

	//���ٵ���
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