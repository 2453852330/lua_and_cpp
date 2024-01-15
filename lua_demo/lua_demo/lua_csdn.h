#pragma once

#include "base_header.h"

namespace CSDN
{
	// helper 
	void csdn_logError(lua_State* L);
	void csdn_logStackCount(lua_State* L);


	// cpp 读取 lua
	// 读取一个全局变量
	void csdn_01();
	// 读取多个全局变量
	void csdn_02();


	// cpp 创建 lua变量

}
