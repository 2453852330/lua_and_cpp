#include "base_test_9_16.h"


typedef struct A
{
	int count;
	int age;
}FA;

typedef struct B
{
	int count;
	int age;
}FB;



void test_09()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// luaL_newmetatable(L, "People");


	
	
	luaL_dofile(L, "user_data.lua");

	lua_close(L);
}
