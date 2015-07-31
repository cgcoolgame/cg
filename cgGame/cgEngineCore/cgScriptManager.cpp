#include "StdAfx.h"
#include "cgScriptManager.h"
#include <string>

using std::string;

cgScriptManager::cgScriptManager(void)
{
	m_pState = NULL;
}

cgScriptManager::~cgScriptManager(void)
{
	Terminate();
}

bool cgScriptManager::Initialize()
{
	m_pState = lua_open();

	if (!m_pState)
		return false;

	luaL_openlibs(m_pState);

	return true;
}

void cgScriptManager::Terminate()
{
	if (m_pState)
		lua_close(m_pState);
}

bool cgScriptManager::RegisterFunc( const char * name, cgScriptFunc func )
{
	lua_register(m_pState, name, func);
	return true;
}

bool cgScriptManager::DoFile( const char * path )
{
	luaL_dofile(m_pState, path);
	return true;
}

bool cgScriptManager::DoString( const char * str )
{
	return DoBuffer(str, strlen(str), "DoString");
}

bool cgScriptManager::DoBuffer( const char * buffer, unsigned len, const char * name )
{
	if (!luaL_loadbuffer(m_pState, buffer, len, name) 
		&& !lua_pcall(m_pState, 0, LUA_MULTRET, 0))
		return true;

	if (lua_gettop(m_pState) > 0 && lua_isstring(m_pState, -1))
	{
		string str = lua_tostring(m_pState, -1);
		lua_pop(m_pState, 1);
		str += "\n\n";
		str += buffer;
	}

	return false;
}
