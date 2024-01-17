#include "lua_template.h"
#include "HelperLib.h"


void LUA_TEMPLATE::lua_template_01()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushstring(L,"string");
	lua_setglobal(L, "name");

	luaL_loadfile(L, "lua_template_01.lua");

	if (lua_pcall(L,0,0,0) != 0)
	{
		HELPER::helper_logError(L);
	}

	lua_close(L);
}
