#include "luaUtility.h"

static void lua_stack_dump (lua_State *L)
{
    int i;
    int top = lua_gettop(L);
    static int count = 0;

    printf("+++ lua stack begin %d +++\n", ++count);
    for (i = 1; i <= top; i++)    /* repeat for each level */
    {
        printf("%d. ", i);
        int t = lua_type(L, i);
        switch (t)
        {

        case LUA_TSTRING:  /* strings */
            printf("`%s'", lua_tostring(L, i));
            break;

        case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;

        case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(L, i));
            break;

        default:  /* other values */
            printf("%s", lua_typename(L, t));
            break;

        }
        printf("\n");  /* put a separator */
    }
    printf("--- lua stack end   ---\n");  /* end the listing */
}

void lua_evaluate_expression(lua_State *L, const char *expr)
{
    lua_pushfstring(L, "return %s", expr);
    luaL_loadstring(L, lua_tostring(L, -1));
    lua_remove(L, -2);
    lua_pcall(L, 0, 1, 0);
}
