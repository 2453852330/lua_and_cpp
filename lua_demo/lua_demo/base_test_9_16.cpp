#include "base_test_9_16.h"


typedef struct People
{
	std::string name;
	int age;
}FPeople;



void test_09()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// luaL_newmetatable(L, "People");


	printf("string size = %d | int size = %d | FPeople size = %d \n", sizeof(std::string), sizeof(int),sizeof(FPeople));

	FPeople* pPeople = (FPeople*)lua_newuserdata(L, sizeof(FPeople));




	
	
	luaL_dofile(L, "user_data.lua");

	lua_close(L);
}
