
////////////////////////////////////////////////
//	FileName:		cgTxtDatabase.h
//	Author:			Master
//	Date:			2014.3.19
//	Description:	操作文本数据库的工具
//	mark:			所有的事情都不能一蹴而就，不断演进也是一种乐趣
////////////////////////////////////////////////

#ifndef cgTxtDataReader_h__
#define cgTxtDataReader_h__
#include <vector>

#define CG_DEFAULT_TEXT_FIELD_NUM 64

class cgTxtRecord
{
public:
	cgTxtRecord();
	~cgTxtRecord();

public:
	// 清空
	void Clear();

	// 获取
	const char * GetField(unsigned index)const;

	// 添加
	void AddField(const char * pcField);

	// 获取数量
	unsigned GetFieldNum()const;
	
private:
	// 增大buffer
	void EnlargeBuffer(unsigned uNum);
private:

	const char ** m_ppFieldList;
	unsigned m_uFieldNum;
	unsigned m_uFieldBuffLen;
};

// 只用作读取txt配置表
// 初始化优先级可以很高
class cgTxtDataReader
{
public:
	cgTxtDataReader(void);
	~cgTxtDataReader(void);

public:
	bool Initialize();

	bool Open(const char * path);
	void Close();
	const cgTxtRecord * Next();

	unsigned GetBufferLen();
	unsigned GetFileDataLen();

private:

	// 保证缓存足够大
	void EnsureEnouphBuffer();

private:
	cgTxtRecord m_kRecord;
	char * m_pBuffer;
	unsigned m_uBufferLen;
	unsigned m_uFileDataLen;
	unsigned m_uBuffOffset;
};

// 配置表字符串转游戏内部字符串
const TCHAR * cgXConfigStr2CgTxt(const char *str);

#endif // cgTxtDatabase_h__
