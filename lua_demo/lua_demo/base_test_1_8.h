#pragma once
#include "base_header.h"


// 栈顶是 -1 , 栈底是 1


// base use
void test_01();


// load lua + run
void test_02();


// 此函数会被注册到Lua中;
static int average(lua_State* L);

void test_03();

// 
void test_04();


// lua function + stack
void test_05();


// lua table
void test_06();



void test_07();


// lua_getglobal(L, "var")会执行两步操作：1.将var放入栈中，2.由Lua去寻找变量var的值，并将变量var的值返回栈顶（替换var）。
// lua_getfield(L, -1, "name")的作用等价于 lua_pushstring(L, "name") + lua_gettable(L, -2)


// call dll
void test_08();


