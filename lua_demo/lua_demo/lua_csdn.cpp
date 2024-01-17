#include "lua_csdn.h"
#include "HelperLib.h"

// https://blog.csdn.net/yingshukun/article/details/119544987
// https://lua.org/manual/5.4/manual.html#lua_type



// 从lua读取变量
void CSDN::csdn_01()
{
	lua_State* L = luaL_newstate();
	// 加载基础库,不然print()函数都无法调用;
	luaL_openlibs(L);

	int load_ret = luaL_loadfile(L, "csdn_01.lua");
	if (load_ret != 0)
	{
		HELPER::helper_logError(L);
		return;
	}

	int call_ret = lua_pcall(L, 0, 0, 0);
	if (call_ret != 0)
	{
		HELPER::helper_logError(L);
		return;
	}

	HELPER::helper_logStackCount(L);

	lua_getglobal(L, "count");
	int count = lua_tointeger(L, -1);
	printf("count = %d \n", count);

	HELPER::helper_logStackCount(L);
	// get table 会把变量压入栈顶
	lua_pop(L, 1);
	//
	printf("after pop \n");
	HELPER::helper_logStackCount(L);


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
		HELPER::helper_logError(L);
		return;
	}

	int call_ret = lua_pcall(L, 0, 0, 0);
	if (call_ret != 0)
	{
		HELPER::helper_logError(L);
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
	lua_State* L = luaL_newstate();

	luaL_openlibs(L);


	lua_pushstring(L, "hello lua");
	lua_setglobal(L, "name");

	lua_pushnumber(L, 12);
	lua_setglobal(L, "count");

	lua_pushboolean(L, true);
	lua_setglobal(L, "isMan");

	// use in lua file 
	HELPER::helper_logStackCount(L);

	//
	if (luaL_loadfile(L, "csdn_03.lua") != 0)
	{
		HELPER::helper_logError(L);
		return;
	}

	if (lua_pcall(L,0,0,0) != 0)
	{
		HELPER::helper_logError(L);
		return;
	}

	lua_close(L);
}

void CSDN::csdn_04()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "csdn_04.lua");

	HELPER::helper_logStackCount(L);

	// push function to stack
	lua_getglobal(L, "testCall");
	// push param
	lua_pushnumber(L, 12.3);
	lua_pushnumber(L, 4.25);

	HELPER::helper_logStackCount("after push function + param",L);


	// pcall
	lua_pcall(L, 2, 1, 0);
	HELPER::helper_logStackCount("after call function",L);

	// get return value from stack
	double ret_value = lua_tonumber(L, -1);
	printf("call lua function, return value : %f \n", ret_value);

	// pop return value
	lua_pop(L, 1);

	lua_close(L);
}


// define cpp function called in lua
// must use this format
int getMax(lua_State* L)
{
	int stack = lua_gettop(L);

	double a = lua_tonumber(L, stack - 1);
	double b = lua_tonumber(L, stack );

	lua_pop(L, 2);

	if (a > b)
	{
		lua_pushboolean(L, true);
	}
	else
	{
		lua_pushboolean(L, false);
	}

	return 1;
}

void CSDN::csdn_05()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, getMax);
	lua_setglobal(L, "getMax");

	luaL_dofile(L, "csdn_05.lua");


	lua_close(L);
}


void CSDN::csdn_06()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "csdn_06.lua");

	HELPER::helper_logStackCount(L);

	/* 读取 Lua 表数据*/

	//lua 中定义的表 mytable = { name = "hello", age = 12 }

	// 将表压入堆栈
	lua_getglobal(L, "mytable");

	// 将Key压入
	lua_pushstring(L, "name");
	// 将Key 值替换为 Value , -2 表示表的索引
	lua_gettable(L, -2);

	const char* name = lua_tostring(L, -1);
	printf("get name from table :%s \n", name);

	// 快捷方式
	// 避免的将 Key 压入栈, idx 表示表的索引,此处依旧为 -2
	lua_getfield(L, -2, "age");
	int age = lua_tointeger(L, -1);
	printf("get age from table:%d \n", age);

	HELPER::helper_logStackCount("after get table",L);
	// 此时栈状态
	// 12
	// hello
	// mytable

	lua_pop(L, 2);  // 此时,栈中只有表的存在   // -3


	/* 修改或添加表数据 */


	// 将值写入 table
	// 首先 push key
	lua_pushstring(L, "good");  // -2
	// push value
	lua_pushnumber(L, 6.6f);  // -1
	lua_settable(L, -3);

	// 设置完之后,会自动出栈 key+value , 只留下 table
	HELPER::helper_logStackCount("set value to table", L);

	// 测试修改表
	lua_pushstring(L, "name");  // -2
	lua_pushstring(L, "this is new name"); // -1
	lua_settable(L, -3);

	lua_pop(L, 1);


	// 获取函数
	lua_getglobal(L, "testA");
	if (lua_pcall(L, 0, 0, 0) != 0 )
	{
		HELPER::helper_logError(L);
		lua_close(L);
		return;
	}

	lua_getglobal(L, "print_table");
	if (lua_pcall(L, 0, 0, 0) != 0)
	{
		HELPER::helper_logError(L);
		lua_close(L);
		return;
	}

	HELPER::helper_logStackCount("after call print_table", L);


	lua_close(L);
}


void CSDN::csdn_07()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "csdn_07.lua");

	lua_close(L);
}


typedef struct UserData
{
	int A;
	int B;
} FUserData;


void CSDN::csdn_08()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	HELPER::helper_logStackCount("before new user data",L);

	FUserData* ud_a = (FUserData*)lua_newuserdata(L, sizeof(FUserData));

	if (ud_a)
	{
		ud_a->A = 12;
		ud_a->B = 32;
	}

	HELPER::helper_logStackCount("after new user data", L);
	lua_setglobal(L, "userinfo");

	HELPER::helper_logStackCount("set user data to global", L);

	lua_getglobal(L, "userinfo");
	HELPER::helper_logStackCount("get user data from global", L);

	FUserData* ud_b = (FUserData*)lua_touserdata(L, -1);

	printf("get data from global lua var , A:%d | B:%d \n", ud_b->A, ud_b->B);
	lua_pop(L, 1);
	HELPER::helper_logStackCount(L);


	lua_close(L);
}



typedef struct student
{
	const char* name = nullptr;
	int age = 0;
	float score = 0.f;
} Student;


int NewStudent(lua_State* L)
{
	// CSDN::HELPER::helper_logStackCount("before create user data",L);
	lua_newuserdata(L, sizeof(Student)); // -2
	// CSDN::HELPER::helper_logStackCount("after create user data , ready to create meta table", L);
	luaL_newmetatable(L, "stu"); // -1
	// CSDN::HELPER::helper_logStackCount("after create meta table , ready to set meta table", L);
	lua_setmetatable(L, -2);
	// CSDN::HELPER::helper_logStackCount("after set meta table", L);

	printf("new student success \n");
	return 1;
}


/* 第三个参数表示表示函数调用时的参数 */
// luaL_argcheck(L, std != nullptr, 1, "check user data");
// 例如 Student.setName(objStudent, "果冻想")   1 表示 objStudent , 2 表示 "果冻想"

int SetStudentName(lua_State* L)
{
	printf("set name called \n");

	Student* std = (Student*)lua_touserdata(L, 1);

	printf("get user data result:%s \n", std ? "true" : "false");

	const char* name = luaL_checkstring(L, 2);
	printf("get name from param result:%s \n", name ? name : "error");

	if (name)
	{
		std->name = name;
		printf("set name success \n");
	}

	return 0;
}

int setStudentAge(lua_State*L)
{
	Student* std = (Student*)lua_touserdata(L, 1);
	int age = luaL_checkinteger(L, 2);
	std->age = age;
	return 0;
}

int setStudentScore(lua_State* L)
{
	Student* std = (Student*)lua_touserdata(L, 1);
	float score = luaL_checknumber(L, 2);
	std->score = score;
	return 0;
}

int LogStudentInfo(lua_State* L)
{
	Student* std = (Student*)lua_touserdata(L, 1);
	printf("log student info called , get user data result : %s \n", std ? "true" : "false");

	if (std)
	{
		lua_pushstring(L, std->name);
		lua_pushinteger(L, std->age);
		lua_pushnumber(L, std->score);
		return 3;
	}

	return 0;
}

int TestFunc(lua_State* L)
{
	lua_pushstring(L, "this is test func");
	return 1;
}

const luaL_Reg StuRegInfo[] = {
	{"new",NewStudent},
	{"log",LogStudentInfo},
	{"setName",SetStudentName},
	{"setAge",setStudentAge},
	{"setScore",setStudentScore},
	{"test",TestFunc},
	{NULL,NULL}
};



void CSDN::csdn_09()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_register(L, "student", StuRegInfo);

	luaL_dofile(L, "csdn_09.lua");

	lua_close(L);
}

