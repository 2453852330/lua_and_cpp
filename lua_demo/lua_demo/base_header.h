#pragma once
#include <iostream>  
#include <string.h>  


extern "C"
{
	// lua.h���ṩʹ��Lua��������к���������ļ��е����к�������lua_Ϊǰ׺��
#include "lua.h"
	// ʹ��lua.h�й����Ĺ���API��Ϊ���������ṩ���߲�εĳ��󡣸��ļ��е����к�������luaL_Ϊǰ׺��
#include "lauxlib.h"
	// �ṩ��׼��Lua�⡣����ļ��е����к���Ҳ����luaL_Ϊǰ׺��
#include "lualib.h"  
}