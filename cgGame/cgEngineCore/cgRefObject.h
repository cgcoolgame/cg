// ���ü����ĳ���
// һ����򵥵�ʵ�ַ�ʽ
// ����ͼƬ����Դ�ĸ�������

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
	static unsigned GetTotalIncrease();
	static unsigned GetTotalDecrease();
#endif

protected:
	virtual void DeleteThis();

protected:
	unsigned m_uRefNum;


#ifdef _DEBUG
	unsigned m_uIncreaseNum;
	unsigned m_uDecreaseNum;

	static unsigned ms_uTotalNum;
	static unsigned ms_uTotalIncrease;
	static unsigned ms_uTotalDecrease;
#endif
};
#endif // CGRefObject_h__

