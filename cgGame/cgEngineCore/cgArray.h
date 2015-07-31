//////////////////////////////////////////////////////////////////////////
// 数组包装
//////////////////////////////////////////////////////////////////////////
#ifndef cgArray_h__
#define cgArray_h__

template<typename T>
class cgArray
{
public:
	cgArray(size_t capacity);
	~cgArray(void);

	inline size_t Capacity();
	inline size_t Size();
	inline bool Empty();

	inline size_t Add(T t);

	inline T Del(size_t index);
	inline bool Del(T t);

	inline T Index(size_t index);
	inline T operator[](size_t index);

	T * Begin();
	T * End();

private:
	inline void Enlarge(size_t deltaSize);

private:
	size_t m_Capacity;
	size_t m_Size;
	T * m_pContent;
};

template<typename T>
bool cgArray<T>::Empty()
{
	return m_Size == 0;
}

template<typename T>
T * cgArray<T>::End()
{
	return m_pContent+m_Size;
}

template<typename T>
T * cgArray<T>::Begin()
{
	return m_pContent;
}

// -------------------------------------------------------------------

template<typename T>
cgArray<T>::cgArray( size_t capacity )
{
	m_pContent = new T[capacity];
	m_Capacity = capacity;
	m_Size = 0;
}

template<typename T>
cgArray<T>::~cgArray( void )
{
	if (m_pContent)
	{
		delete[] m_pContent;
		m_pContent = NULL;
	}
}

template<typename T>
size_t cgArray<T>::Capacity()
{
	return m_Capacity;
}

template<typename T>
size_t cgArray<T>::Size()
{
	return m_Size;
}

template<typename T>
size_t cgArray<T>::Add( T t )
{
	if (m_Size >= m_Capacity)
		Enlarge(m_Capacity);
	
	m_pContent[m_Size++] = t;
	return m_Size;
}

template<typename T>
void cgArray<T>::Enlarge( size_t deltaSize )
{
	T * pNewContent = new T[m_Capacity + deltaSize];
	for (size_t i = 0; i < m_Capacity; ++i)
	{
		pNewContent[i] = m_pContent[i];
	}
	m_Capacity += deltaSize;
}

template<typename T>
T cgArray<T>::Index( size_t index )
{
	if (index < m_Size)
		return m_pContent[index];

	return T();
}

template<typename T>
T cgArray<T>::operator[]( size_t index )
{
	return Index(index);
}

template<typename T>
bool cgArray<T>::Del( T t )
{
	for (size_t i = 0; i < m_Size; ++i)
	{
		if (m_pContent[i] == t)
		{
			m_pContent[i] == m_pContent[--m_Size];
			return true;
		}
	}

	return false;
}

template<typename T>
T cgArray<T>::Del( size_t index )
{
	T t;
	if (index < m_Size)
	{
		t = m_pContent[index];
		m_pContent[index] == m_pContent[--m_Size];
	}

	return t;
}
#endif // cgArray_h__
