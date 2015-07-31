#ifndef cgStringTable_h__
#define cgStringTable_h__

#include "cgsingleton.h"

// �������ȼ����ߣ���Ӧ�÷űȽ���
class cgStringTable :
	public cgSingleton<cgStringTable>
{
public:
	cgStringTable(void);
	~cgStringTable(void);

public:
	bool Initialize();

	const char * UnicodeToAcp(const wchar_t * str );
	const wchar_t * AcpToUnicode(const char * str);

	const char * UnicodeToUtf8(const wchar_t * str);
	const wchar_t * Utf8ToUnicode(const char * str);

private:
	char * m_pCharBuffer;		// խ�ַ�����
	int m_nCharBufferLen;	// խ�ַ����泤��

	wchar_t * m_pWCharBuffer;		// ���ַ�����
	int m_nWCharBufferLen;	// ���ַ����泤��
};

const TCHAR * cgXAcp2cgTxt(const char * str);
const TCHAR * cgXUtf8TocgTxt(const char * str);

#endif // cgStringTable_h__
