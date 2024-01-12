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


// ���嵼������
// ���� Lua �е��� require "myLubLib" ʱ:
// lua ������ִ��
// local path = "myLuaLib.dll"								-- ָ��DLL
// local f = package.loadlib(path, "luaopen_myLuaLib")		-- ��DLL���� luaopen_myLuaLib ����
// f()														-- Ȼ������������

// ���Ժ������� luaopen_ģ�����ĺ����ᱻ�Զ�����;
// �����Ƽ�DLL�����趨Ϊģ������;
extern "C" LUA_API int luaopen_myLuaLib(lua_State * L);