
#ifndef cgScriptManager_h__
#define cgScriptManager_h__

#define _USE_LUA_SCRIPT_

#ifdef _USE_LUA_SCRIPT_

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <process.h>
}

typedef lua_CFunction cgScriptFunc;

#endif

class cgScriptManager
{
public:
	cgScriptManager(void);
	~cgScriptManager(void);

	bool Initialize();
	void Terminate();

	bool RegisterFunc(const char * name, cgScriptFunc func);

	bool DoFile(const char * path);
	bool DoString(const char * str);
	bool DoBuffer(const char * buffer, unsigned len, const char * name);

protected:
	lua_State * m_pState;
};


#endif // cgScriptManager_h__
