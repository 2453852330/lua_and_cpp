#include "lua_class.h"
#include "HelperLib.h"

void LUA_CLASS::lua_class_01()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_loadfile(L, "lua_class_01.lua");

	if (lua_pcall(L, 0, 0, 0) !=  0)
	{
		HELPER::helper_logError(L);
	}


	lua_close(L);
}

void LUA_CLASS::lua_class_02()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_loadfile(L, "lua_class_02.lua");

	if (lua_pcall(L, 0, 0, 0) != 0)
	{
		HELPER::helper_logError(L);
	}


	lua_close(L);
}
