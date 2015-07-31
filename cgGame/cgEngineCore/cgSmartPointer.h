// �����ü�����ϵ�����ָ��
// һ�δ󵨵ĳ���

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

	// ���ƹ�������
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
	// ���Ʋ���������
	inline cgSmartPointer& operator=(const cgSmartPointer & kPointer)
	{
		if (kPointer.m_pkRefObject != m_pkRefObject)
		{
			DecreaseRef();
			m_pkRefObject = kPointer.m_pkRefObject;
			IncreaseRef();
		}
		return * this;
	}

	// ָ�븳ֵ����������
	inline cgSmartPointer& operator=(T* pkRefObject)
	{
		if (m_pkRefObject != pkRefObject)
		{
			DecreaseRef();
			m_pkRefObject = pkRefObject;
			IncreaseRef();
		}

		return *this;
	}

	inline bool operator== (const cgSmartPointer& ptr) const
	{
		return m_pkRefObject == ptr.m_pkRefObject;
	}

	inline bool operator== (const T* pkRef) const
	{
		return m_pkRefObject == pkRef;
	}

	inline bool operator !=(const cgSmartPointer& ptr) const
	{
		return m_pkRefObject != ptr.m_pkRefObject;
	}

	inline bool operator !=(const T* pkRef) const
	{
		return m_pkRefObject != pkRef;
	}

	// ָ��
	inline T * operator->()
	{
		return m_pkRefObject;
	}

	// ����ָ��ָ��
	inline const T * operator->() const
	{
		return m_pkRefObject;
	}

	// ������
	inline T & operator*()
	{
		return *m_pkRefObject;
	}

	// ����ָ�������
	inline const T & operator*() const
	{
		return *m_pkRefObject;
	}

	// ȡ��ַ
	inline T* operator &()
	{
		return m_pkRefObject;
	}

	// ȡ��ַ
	inline const T* operator &()const
	{
		return m_pkRefObject;
	}

	// ����ֵǿת��������
	inline operator bool() const
	{
		return m_pkRefObject != NULL;
	}

private:
	inline void IncreaseRef()
	{
		if (m_pkRefObject)
			m_pkRefObject->IncreaseRef();
	}
	inline void DecreaseRef()
	{
		if (m_pkRefObject)
			m_pkRefObject->DecreaseRef();
	}
private:
	T * m_pkRefObject;
};

#endif // CGSmartPointer_h__

