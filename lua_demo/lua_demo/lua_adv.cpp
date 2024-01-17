#include "lua_adv.h"
#include "HelperLib.h"

typedef struct point
{
	float x, y, z;
} FPoint;

int NewPoint(lua_State* L)
{
	FPoint* p = (FPoint*)lua_newuserdata(L, sizeof(FPoint));
	if (p)
	{
		p->x = 0.f;
		p->y = 0.f;
		p->z = 0.f;
		return 1;
	}
	return 1;
}

int SetPoint(lua_State* L)
{
	printf("set point called , stack count:%d \n", lua_gettop(L));

	FPoint* p = (FPoint*)lua_touserdata(L, 1);

	luaL_argcheck(L, p != nullptr, 1, "lua state is nullptr");
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);

	

	if (p)
	{
		p->x = x;
		p->y = y;
		p->z = z;
	}
	return 0;
}

int GetPoint(lua_State* L)
{
	FPoint* p = (FPoint*)lua_touserdata(L, 1);
	luaL_argcheck(L, p != nullptr, 1, "lua state is nullptr");

	lua_pushnumber(L, p->x);
	lua_pushnumber(L, p->y);
	lua_pushnumber(L, p->z);

	return 3;
}



const luaL_Reg RegList[] = {
	{"new", NewPoint},
	{"set", SetPoint},
	{"get", GetPoint},
	{NULL,NULL}
};



void CT::adv_01()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_register(L, "point", RegList);

	luaL_dofile(L, "adv_01.lua");


	lua_close(L);
}


// test(12,true,"helloworld")
int register_02(lua_State* L)
{
	printf("register_02 \n");

	// 结果=3,刚好是参数个数;
	int stack = lua_gettop(L);
	printf("stack count:%d \n", stack);

	// 参数会被正序压栈,需要逆向读取
	const char* str = lua_tostring(L, -1);
	printf("try get str:%s \n", str);

	bool b = lua_toboolean(L, -2);
	printf("try get bool:%s \n", b ? "true" : "false");

	int c = lua_tointeger(L, -3);
	printf("try get int:%d \n", c);

	return 0;
}

void CT::adv_02()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	HELPER::helper_logStackCount("before push function", L);

	lua_pushcfunction(L, register_02);
	lua_setglobal(L, "test");

	HELPER::helper_logStackCount("after push function", L);


	luaL_dofile(L, "adv_02.lua");

	HELPER::helper_logStackCount("after call lua function", L);

	lua_close(L);
}

/* -------------------------------------------------------------------------------------------------------------*/

typedef struct Base
{
	const char* name = nullptr;
	int age = 0;

	void log()
	{
		printf("Log FBase Object: name:%s | age:%d \n", name, age);
	}
} FBase;


// 可以截获到GC函数,但是 UserData 是由 Lua 管理的,所以不用处理
int BaseGC(lua_State* L)
{
	printf("Base GC \n");
	//
	FBase* base =(FBase *) luaL_checkudata(L, 1, "Base");
	luaL_argcheck(L, base != nullptr, 1, "gc check param valid");

	return 0;
}



int NewBase(lua_State* L)
{
	FBase* base = (FBase*) lua_newuserdata(L, sizeof(FBase));

	luaL_getmetatable(L, "Base");
	// stack info
	// metatable		-1
	//  userdata		-2
	lua_setmetatable(L, -2);



	return 1;
}



int SetBase(lua_State*L)
{
	FBase* base = (FBase*) luaL_checkudata(L, 1, "Base");
	luaL_argcheck(L, base != nullptr, 1, "get base user data error");

	luaL_checktype(L, 2, LUA_TSTRING);
	const char * name = luaL_checkstring(L, 2);
	luaL_argcheck(L,name != nullptr,2,"the name param is nullptr");

	luaL_checktype(L, 3, LUA_TNUMBER);
	int age = luaL_checkinteger(L, 3);
	luaL_argcheck(L, age > 0, 3, "the age is <= 0");

	if (base)
	{
		base->name = name;
		base->age = age;
	}
	return 0;
}

int LogBase(lua_State*L)
{
	FBase* base = (FBase*)luaL_checkudata(L, 1, "Base");
	luaL_argcheck(L, base != nullptr, 1, "base user data is nullptr");

	if (base)
	{
		base->log();
	}
	return 0;
}

const luaL_Reg BaseRegList[] = {
	{"new",NewBase},
	{"set",SetBase},
	{"log",LogBase},
	{NULL,NULL}
};

int testCall(lua_State* L)
{
	printf("test called \n");
	return 0;
}

int testToString(lua_State* L)
{
	FBase* base = (FBase*)luaL_checkudata(L, 1, "Base");
	luaL_argcheck(L, base != nullptr, 1, "base user data is nullptr");
	lua_pushstring(L, "__tostring is called \n");
	return 1;
}

void CT::adv_03()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// 创建全局 metatable ,用于标记 userdata
	luaL_newmetatable(L, "Base");
	
					
	lua_pushcfunction(L, BaseGC);
	// stack info
	// base gc				-1
	// metatable			-2
	lua_setfield(L, -2, "__gc");

	lua_pushcfunction(L, testCall);
	lua_setfield(L, -2, "testCall");

	lua_pushcfunction(L, testToString);
	lua_setfield(L, -2, "__tostring");


	// 批量注册,跳过new函数注册
	for (int i = 1; i < 3; ++i)
	{
		lua_pushcfunction(L, BaseRegList[i].func);
		lua_setfield(L, -2, BaseRegList[i].name);
	}

	// 注册函数 , 如果要用 : 引用函数,必须设置 __index  == 他自身
	// 将idx索引上的值的副本压入栈顶
	lua_pushvalue(L, -1);
	// copy metatable			-1
	// meta table				-2
	lua_setfield(L, -2, "__index");


	
	luaL_register(L,"FBase", BaseRegList);

	luaL_loadfile(L, "adv_03.lua");

	if (lua_pcall(L,0,0,0) != 0)
	{
		HELPER::helper_logError(L);
		lua_close(L);
		return;
	}

	lua_close(L);
}

void CT::adv_04()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_loadfile(L, "adv_04.lua");

	if (lua_pcall(L,0,0,0) != 0)
	{
		HELPER::helper_logError(L);
	}

	lua_close(L);
}
