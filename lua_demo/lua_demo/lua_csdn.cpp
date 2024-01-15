#include "lua_csdn.h"

// https://blog.csdn.net/yingshukun/article/details/119544987
// https://lua.org/manual/5.4/manual.html#lua_type


void CSDN::csdn_logError(lua_State* L)
{
	const char* err = lua_tostring(L, -1);
	printf("lua Error:%s \n", err);
}

void CSDN::csdn_logStackCount(lua_State* L)
{
	printf("log Stack Count:%d \n", lua_gettop(L));
}

// 从lua读取变量
void CSDN::csdn_01()
{
	lua_State* L = luaL_newstate();
	// 加载基础库,不然print()函数都无法调用;
	luaL_openlibs(L);

	int load_ret = luaL_loadfile(L, "csdn_01.lua");
	if (load_ret != 0)
	{
		csdn_logError(L);
		return;
	}

	int call_ret = lua_pcall(L, 0, 0, 0);
	if (call_ret != 0)
	{
		csdn_logError(L);
		return;
	}

	csdn_logStackCount(L);

	lua_getglobal(L, "count");
	int count = lua_tointeger(L, -1);
	printf("count = %d \n", count);

	csdn_logStackCount(L);
	// get table 会把变量压入栈顶
	lua_pop(L, 1);
	//
	printf("after pop \n");
	csdn_logStackCount(L);


	lua_close(L);
}

void CSDN::csdn_02()
{
	lua_State* L = luaL_newstate();
	// 加载基础库,不然print()函数都无法调用;
	luaL_openlibs(L);

	int load_ret = luaL_loadfile(L, "csdn_02.lua");
	if (load_ret != 0)
	{
		csdn_logError(L);
		return;
	}

	int call_ret = lua_pcall(L, 0, 0, 0);
	if (call_ret != 0)
	{
		csdn_logError(L);
		return;
	}



	int stack_top = lua_gettop(L);
	// get 3 global var
	lua_getglobal(L, "name");
	lua_getglobal(L, "count");
	lua_getglobal(L, "isMan");


	// 不要硬编码索引。相反，始终使用相对于已知偏移量的索引。
	// 通过栈顶索引计算真实索引,保证stack不会出错
	bool bIsMan = lua_toboolean(L, stack_top + 1);
	int Count = lua_tointeger(L, stack_top + 2);
	const char* Name = lua_tostring(L, stack_top + 3);


	printf("read global var from lua: name:%s | count:%d | isMan:%d \n", Name, Count, bIsMan);

	lua_pushstring(L, "good");
	const char* name_A = lua_tostring(L, -1);
	printf("new name test:%s \n", name_A);

	// clear stack
	lua_pop(L, 4);


	lua_close(L);
}

void CSDN::csdn_03()
{

}
