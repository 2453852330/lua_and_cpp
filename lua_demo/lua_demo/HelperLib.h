#pragma once
#include "base_header.h"


namespace HELPER
{
	// helper 
	void helper_logError(lua_State* L);
	void helper_logStackCount(lua_State* L);
	void helper_logStackCount(const char* Info, lua_State* L);
}
