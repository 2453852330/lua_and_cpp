#pragma once

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#ifdef LUA_EXPORTS
#define  LUA_API __declspec(dllexport)
#else
#define LUA_API __declspec(dllimport)
#endif


// 定义导出函数
// 当在 Lua 中调用 require "myLubLib" 时:
// lua 会如下执行
// local path = "myLuaLib.dll"								-- 指定DLL
// local f = package.loadlib(path, "luaopen_myLuaLib")		-- 从DLL加载 luaopen_myLuaLib 函数
// f()														-- 然后调用这个函数

// 所以函数形如 luaopen_模块名的函数会被自动调用;
// 所以推荐DLL名称设定为模块名称;
extern "C" LUA_API int luaopen_myLuaLib(lua_State * L);