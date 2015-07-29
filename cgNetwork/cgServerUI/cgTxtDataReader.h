
////////////////////////////////////////////////
//	FileName:		cgTxtDatabase.h
//	Author:			Master
//	Date:			2014.3.19
//	Description:	�����ı����ݿ�Ĺ���
//	mark:			���е����鶼����һ����ͣ������ݽ�Ҳ��һ����Ȥ
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
	// ���
	void Clear();

	// ��ȡ
	const char * GetField(unsigned index)const;

	// ���
	void AddField(const char * pcField);

	// ��ȡ����
	unsigned GetFieldNum()const;
	
private:
	// ����buffer
	void EnlargeBuffer(unsigned uNum);
private:

	const char ** m_ppFieldList;
	unsigned m_uFieldNum;
	unsigned m_uFieldBuffLen;
};

// ֻ������ȡtxt���ñ�
// ��ʼ�����ȼ����Ժܸ�
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

	// ��֤�����㹻��
	void EnsureEnouphBuffer();

private:
	cgTxtRecord m_kRecord;
	char * m_pBuffer;
	unsigned m_uBufferLen;
	unsigned m_uFileDataLen;
	unsigned m_uBuffOffset;
};

// ���ñ��ַ���ת��Ϸ�ڲ��ַ���
const TCHAR * cgXConfigStr2CgTxt(const char *str);

#endif // cgTxtDatabase_h__
