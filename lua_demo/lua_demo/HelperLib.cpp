#include "HelperLib.h"

void HELPER::helper_logError(lua_State* L)
{
	const char* err = lua_tostring(L, -1);
	printf("lua Error:%s \n", err);
}

void HELPER::helper_logStackCount(lua_State* L)
{
	printf("log Stack Count:%d \n", lua_gettop(L));
}

void HELPER::helper_logStackCount(const char* Info, lua_State* L)
{
	printf("%s : log Stack Count:%d \n", Info, lua_gettop(L));
}
