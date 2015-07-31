#ifndef cgStringDef_h__
#define cgStringDef_h__

#include <string>
using std::string;

#define  cgStrLen _tcsclen
#define  cgStrCpy _tcscpy_s
#define  cgStrCmp _tcscmp
#define  cgStrToLong _tcstol
#define  cgStrToULong _tcstoul

#ifdef UNICODE
	#define	cgSprintf swprintf_s
	typedef	std::wstring cgString;
#else
	#define	cgSprintf sprintf_s
	typedef	std::string cgString;
#endif

#define CG_MAX_IMAGE_PATH_LEN 256
#define CG_SHORT_TEXT_BUFF_LEN	 64
#define CG_NORMAL_TEXT_BUFF_LEN 256
#define CG_LONG_TEXT_BUFF_LEN	1024
#define CG_LONG_LONG_TEXT_BUFF_LEN 4096

#endif // cgStringDef_h__
