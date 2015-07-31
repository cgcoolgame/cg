// 引用计数的尝试
// 一种最简单的实现方式
// 用于图片等资源的各种引用

#ifndef CGRefObject_h__
#define CGRefObject_h__

class cgRefObject
{
public:
	cgRefObject(void);
	virtual ~cgRefObject(void);
public:
	void IncreaseRef();
	void DecreaseRef();

	unsigned GetRefNum() const;

#ifdef _DEBUG
	unsigned GetIncreaseNum() const;
	unsigned GetDecreaseNum() const;

	static unsigned GetTotalObjectNum();
#endif

protected:
	virtual void DeleteThis();

protected:
	unsigned m_uRefNum;


#ifdef _DEBUG
	unsigned m_uIncreaseNum;
	unsigned m_uDecreaseNum;

	static unsigned ms_uTotalNum;
#endif
};
#endif // CGRefObject_h__

