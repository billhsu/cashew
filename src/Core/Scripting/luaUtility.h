#ifndef _LUA_UTILITY_H_
#define _LUA_UTILITY_H_

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

void lua_stack_dump (lua_State *L);
void lua_evaluate_expression(lua_State *L, const char *expr);

#endif