#include <assert.h>

#ifndef cgStorage_h__
#define cgStorage_h__

// һ���Ż����Ĵ洢�ֿ�
// ����Ļ�����ͨ����ŵ�
// ����ÿ�β��Һͱ������ܿ���

template<typename T>
class cgStorage
{
public:
	cgStorage(unsigned capacity);
	virtual ~cgStorage(void);

public:

	// ��ȡ����
	unsigned Capacity();

	//// ���Ӳֿ�������uAdd�����¼�����������������=ԭ��������+uAdd
	bool Enlarge(unsigned uAdd);

	// ���һ���������ֵ������id
	// ���idΪ�Ƿ�ֵ��˵�������������
	cgID Add(T *);

	// ɾ��һ������
	// ������ﲻ���ڣ��򷵻�false
	// ���෵��true
	// ע�⣺ֻ�ǴӲֿ����ߣ����ﲻ�ᱻ�ֿ�����,���Ƿ���
	T* Remove(cgID id);

	// ��ȡ��������
	unsigned Size();

	// ˳�����
	T * Index(size_t index);

	// ͨ��id���һ���
	T * Find(cgID id);

protected:
	unsigned m_uCapacity;	// ����
	unsigned m_uUsedIDNum;		// ��������

	cgID * m_pIDList;	// id�б�

	struct Item
	{
		size_t index;	// ����Ʒ��id��id����������������ڷ���
		T * pContent;	// ����
	};

	Item * m_pItemList;
};


// ---------------------------------------------------------------------------------------
template<typename T>
cgStorage<T>::cgStorage( unsigned capacity )
{
	m_uCapacity = capacity;
	m_uUsedIDNum = 0;

	m_pItemList = new Item[capacity];

	m_pIDList = new cgID[capacity];
	for (unsigned i = 0; i < capacity; ++i)
	{
		m_pIDList[i] = i;
	}
}


template<typename T>
cgStorage<T>::~cgStorage( void )
{
	m_uUsedIDNum = 0;
	delete[] m_pItemList;
	delete[] m_pIDList;
}


template<typename T>
bool cgStorage<T>::Enlarge( unsigned uAdded )
{
	cgID * pNewIDList = new cgID[m_uCapacity+uAdded];
	Item * pNewItemList = new Item[m_uCapacity+uAdded];

	memcpy(pNewIDList, m_pIDList, m_uCapacity*sizeof(cgID) );
	for (unsigned i = m_uCapacity; i < m_uCapacity+uAdded; ++i)
	{
		pNewIDList[i] = i;
	}

	memcpy(pNewIDList, m_pItemList, m_uCapacity*sizeof(T*) );
	memset(pNewIDList+m_uCapacity, NULL, uAdded);

	delete[] m_pIDList;
	delete[] m_pItemList;

	m_pIDList = pNewIDList;
	m_pItemList = pNewItemList;

	m_uCapacity += uAdded;

	return true;
}


template<typename T>
unsigned cgStorage<T>::Size()
{
	return m_uUsedIDNum;
}

template<typename T>
unsigned cgStorage<T>::Capacity()
{
	return m_uCapacity;
}

template<typename T>
T * cgStorage<T>::Find( cgID id )
{
	if (id < m_uCapacity)
	{
		return m_pItemList[id].pContent;
	}
	return NULL;
}


template<typename T>
T * cgStorage<T>::Index( size_t index )
{
	if (index < Size())
	{
		Item & item = m_pItemList[m_pIDList[index]];
		assert(item.index == index);
		return item.pContent;
	}

	return NULL;
}

template<typename T>
cgID cgStorage<T>::Add( T * pT)
{
	if (!pT)
		return CG_INVALID_ID;

	if (m_uUsedIDNum >= m_uCapacity )
		Enlarge(m_uCapacity);

	// ������ݣ�ֻ��Ҫ�ѵ�һ�����õ�id�õ�
	cgID id = m_pIDList[m_uUsedIDNum];
	m_pItemList[id].pContent = pT;
	m_pItemList[id].index = m_uUsedIDNum;

	m_uUsedIDNum++;

	return id;
}


template<typename T>
T* cgStorage<T>::Remove( cgID id )
{
	T * pT = NULL;
	if (id < m_uCapacity)
	{
		--m_uUsedIDNum;

		// �Ѿ���ʹ�õġ��Ϸ���id��һ�����Զ�λ���ǿյĺϷ��Ļ����
		pT = m_pItemList[id].pContent;
		m_pItemList[id].pContent = NULL;

		// ���Ƴ���Ԫ�ص�ԭʼindex
		size_t index = m_pItemList[id].index;
		cgID tail = m_pIDList[m_uUsedIDNum];

		// ĩβԪ�غ͸ո��Ƴ����Ǹ�id����λ��
		m_pIDList[index] = tail;

		// id�����󣬶�ӦԪ�����°�index
		m_pItemList[tail].index = index;

		// id����
		m_pIDList[m_uUsedIDNum] = id;
	}

	return pT;
}

#endif // cgStorage_h__
