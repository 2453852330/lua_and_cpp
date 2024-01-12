#include "pch.h"
#include "myfunc.h"

static int sayHelloFunc(lua_State*L)
{
	printf("hello world from dll \n");
	return 0;
}

static int average(lua_State* L)
{
	// 获取堆栈长度,也就是参数长度
	int n = lua_gettop(L);
	double sum = 0;

	for (int i = 1; i <= n; ++i)
	{
		sum += lua_tonumber(L, i);
	}
	// 压入两个值
	lua_pushnumber(L, sum / n);
	lua_pushnumber(L, sum);
	// 返回2个值
	return 2;
}

static const struct luaL_Reg myLib[] =
{
	{"average",average},
	{"sayHello",sayHelloFunc},
	{NULL,NULL} // 必须用NULL表示结束;
};

int luaopen_myLuaLib(lua_State* L)
{
	// 调用注册函数
	// 其中 ss 是模块名,用来在 Lua 中调用函数,形如  ss.sayHelloFunc / ss.average
	luaL_register(L, "ss", myLib);
	return 0;
}
