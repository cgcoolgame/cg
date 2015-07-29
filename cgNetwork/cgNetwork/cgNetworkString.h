#ifndef cgNetworkString_h__
#define cgNetworkString_h__

#include <Windows.h>

const char* Unicode2UTF8(LPCTSTR str);
LPCTSTR UTF8ToUnicode(const char* str);

#endif // cgNetworkString_h__
