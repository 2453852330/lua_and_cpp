#pragma once
#include "base_header.h"


// ջ���� -1 , ջ���� 1


// base use
void test_01();


// load lua + run
void test_02();


// �˺����ᱻע�ᵽLua��;
static int average(lua_State* L);

void test_03();

// 
void test_04();


// lua function + stack
void test_05();


// lua table
void test_06();



void test_07();


// lua_getglobal(L, "var")��ִ������������1.��var����ջ�У�2.��LuaȥѰ�ұ���var��ֵ����������var��ֵ����ջ�����滻var����
// lua_getfield(L, -1, "name")�����õȼ��� lua_pushstring(L, "name") + lua_gettable(L, -2)


// call dll
void test_08();


