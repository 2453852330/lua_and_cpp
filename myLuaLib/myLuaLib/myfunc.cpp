#include "pch.h"
#include "myfunc.h"

static int sayHelloFunc(lua_State*L)
{
	printf("hello world from dll \n");
	return 0;
}

static int average(lua_State* L)
{
	int n = lua_gettop(L);
	double sum = 0;

	for (int i = 1; i <= n; ++i)
	{
		sum += lua_tonumber(L, i);
	}

	lua_pushnumber(L, sum / n);
	lua_pushnumber(L, sum);
	return 2;
}

static const struct luaL_Reg myLib[] =
{
	{"average",average},
	{"sayHello",sayHelloFunc},
	{NULL,NULL}
};

int luaopen_myLuaLib(lua_State* L)
{
	luaL_register(L, "ss", myLib);
	return 0;
}
