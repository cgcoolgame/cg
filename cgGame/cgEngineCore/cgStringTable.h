#ifndef cgStringTable_h__
#define cgStringTable_h__

#include "cgsingleton.h"

// 此类优先级更高，故应该放比较早
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
	char * m_pCharBuffer;		// 窄字符缓存
	int m_nCharBufferLen;	// 窄字符缓存长度

	wchar_t * m_pWCharBuffer;		// 宽字符缓存
	int m_nWCharBufferLen;	// 宽字符缓存长度
};

const TCHAR * cgXAcp2cgTxt(const char * str);
const TCHAR * cgXUtf8TocgTxt(const char * str);

#endif // cgStringTable_h__
