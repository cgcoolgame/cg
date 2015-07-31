#include <assert.h>

#ifndef cgStorage_h__
#define cgStorage_h__

// 一个优化过的存储仓库
// 里面的货物是通过编号的
// 所以每次查找和遍历都很快速

template<typename T>
class cgStorage
{
public:
	cgStorage(unsigned capacity);
	virtual ~cgStorage(void);

public:

	// 获取容量
	unsigned Capacity();

	//// 增加仓库容量，uAdd代表新加容量，扩充后的容量=原来的容量+uAdd
	bool Enlarge(unsigned uAdd);

	// 添加一个货物，返回值代表其id
	// 如果id为非法值，说明超出最大容量
	cgID Add(T *);

	// 删除一个货物
	// 如果货物不存在，则返回false
	// 其余返回true
	// 注意：只是从仓库移走，货物不会被仓库销毁,而是返回
	T* Remove(cgID id);

	// 获取货物数量
	unsigned Size();

	// 顺序查找
	T * Index(size_t index);

	// 通过id查找货物
	T * Find(cgID id);

protected:
	unsigned m_uCapacity;	// 容量
	unsigned m_uUsedIDNum;		// 货物数量

	cgID * m_pIDList;	// id列表

	struct Item
	{
		size_t index;	// 该物品的id在id表里面的索引，用于反查
		T * pContent;	// 内容
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

	// 添加内容，只需要把第一个可用的id用掉
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

		// 已经被使用的、合法的id，一定可以定位到非空的合法的货物的
		pT = m_pItemList[id].pContent;
		m_pItemList[id].pContent = NULL;

		// 被移除的元素的原始index
		size_t index = m_pItemList[id].index;
		cgID tail = m_pIDList[m_uUsedIDNum];

		// 末尾元素和刚刚移除的那个id交换位置
		m_pIDList[index] = tail;

		// id交换后，对应元素重新绑定index
		m_pItemList[tail].index = index;

		// id回收
		m_pIDList[m_uUsedIDNum] = id;
	}

	return pT;
}

#endif // cgStorage_h__
