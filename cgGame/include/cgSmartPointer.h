// 与引用计数配合的智能指针
// 一次大胆的尝试

#ifndef CGSmartPointer_h__
#define CGSmartPointer_h__

template<typename T>
class cgSmartPointer
{
public:
	cgSmartPointer(void)
	{
		m_pkRefObject = NULL;
	}
	~cgSmartPointer(void)
	{
		DecreaseRef();
	}

	// 复制构建函数
	cgSmartPointer(const cgSmartPointer& kPointer)
	{
		m_pkRefObject = kPointer.m_pkRefObject;
		IncreaseRef();
	}

	cgSmartPointer(T * pkRefObject)
	{
		m_pkRefObject = pkRefObject;
		IncreaseRef();
	}

public:
	// 复制操作符重载
	cgSmartPointer& operator=(const cgSmartPointer & kPointer)
	{
		if (kPointer.m_pkRefObject != m_pkRefObject)
		{
			DecreaseRef();
			m_pkRefObject = kPointer.m_pkRefObject;
			IncreaseRef();
		}
		return * this;
	}

	// 指针赋值操作符重载
	cgSmartPointer& operator=(T* pkRefObject)
	{
		if (m_pkRefObject != pkRefObject)
		{
			DecreaseRef();
			m_pkRefObject = pkRefObject;
			IncreaseRef();
		}

		return *this;
	}

	bool operator== (const cgSmartPointer& ptr) const
	{
		return m_pkRefObject == ptr.m_pkRefObject;
	}

	bool operator== (const T* pkRef) const
	{
		return m_pkRefObject == pkRef;
	}

	bool operator !=(const cgSmartPointer& ptr) const
	{
		return m_pkRefObject != ptr.m_pkRefObject;
	}

	bool operator !=(const T* pkRef) const
	{
		return m_pkRefObject != pkRef;
	}

	// 指针
	T * operator->()
	{
		return m_pkRefObject;
	}

	// 常量指针指针
	const T * operator->() const
	{
		return m_pkRefObject;
	}

	// 解引用
	T & operator*()
	{
		return *m_pkRefObject;
	}

	// 常量指针解引用
	const T & operator*() const
	{
		return *m_pkRefObject;
	}

	// 取地址
	T* operator &()
	{
		return m_pkRefObject;
	}

	// 取地址
	const T* operator &()const
	{
		return m_pkRefObject;
	}

	// 布尔值强转符号重载
	operator bool() const
	{
		return m_pkRefObject != NULL;
	}

private:
	void IncreaseRef()
	{
		if (m_pkRefObject)
			m_pkRefObject->IncreaseRef();
	}
	void DecreaseRef()
	{
		if (m_pkRefObject)
			m_pkRefObject->DecreaseRef();
	}
private:
	T * m_pkRefObject;
};

#endif // CGSmartPointer_h__

