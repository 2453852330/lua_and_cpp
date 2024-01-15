#pragma once
#include <iostream>  
#include <string.h>  


extern "C"
{
	// lua.h：提供使用Lua所需的所有函数。这个文件中的所有函数都以lua_为前缀。
#include "lua.h"
	// 使用lua.h中公开的公共API，为常见任务提供更高层次的抽象。该文件中的所有函数都以luaL_为前缀。
#include "lauxlib.h"
	// 提供标准的Lua库。这个文件中的所有函数也都以luaL_为前缀。
#include "lualib.h"  
}