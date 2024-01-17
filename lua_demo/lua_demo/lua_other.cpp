#include "lua_other.h"
#include "HelperLib.h"


void LUA_OTHER::lua_other_01()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// luaL_loadfile(L, "lua_other_01_1.lua");
	// luaL_loadfile(L, "lua_other_01_2.lua");
	// luaL_loadfile(L, "lua_other_01_3.lua");
	luaL_loadfile(L, "lua_other_01_4.lua");

	if (lua_pcall(L,0,0,0) != 0)
	{
		HELPER::helper_logError(L);
	}


	lua_close(L);
}
