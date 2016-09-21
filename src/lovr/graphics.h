#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "../vendor/map/map.h"

map_int_t BufferDrawModes;
map_int_t BufferUsages;

extern const luaL_Reg lovrGraphics[];
int l_lovrGraphicsInit(lua_State* L);
int l_lovrGraphicsClear(lua_State* L);
int l_lovrGraphicsPresent(lua_State* L);
int l_lovrGraphicsGetClearColor(lua_State* L);
int l_lovrGraphicsSetClearColor(lua_State* L);
int l_lovrGraphicsGetShader(lua_State* L);
int l_lovrGraphicsSetShader(lua_State* L);
int l_lovrGraphicsPush(lua_State* L);
int l_lovrGraphicsPop(lua_State* L);
int l_lovrGraphicsNewBuffer(lua_State* L);
int l_lovrGraphicsNewModel(lua_State* L);
int l_lovrGraphicsNewShader(lua_State* L);
