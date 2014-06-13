/*
** $Id: linit.c,v 1.14.1.1 2007/12/27 13:02:25 roberto Exp $
** Initialization of libraries for lua.c
** See Copyright Notice in lua.h
*/


#define linit_c
#define LUA_LIB

#include "lua.h"

#include "lualib.h"
#include "lauxlib.h"

extern int luaopen_socket_core(lua_State *L);
extern int luaopen_crypto(lua_State *L);
extern int luaopen_cmsgpack(lua_State *L);
extern int luaopen_cjson(lua_State *L);
extern int luaopen_dbdsqlite3(lua_State *L);
extern int luaopen_dbdmysql(lua_State *L);

static const luaL_Reg lualibs[] = {
  {"", luaopen_base},
  {LUA_LOADLIBNAME, luaopen_package},
  {LUA_TABLIBNAME, luaopen_table},
  {LUA_IOLIBNAME, luaopen_io},
  {LUA_OSLIBNAME, luaopen_os},
  {LUA_STRLIBNAME, luaopen_string},
  {LUA_MATHLIBNAME, luaopen_math},
  {LUA_DBLIBNAME, luaopen_debug},
#ifdef WITH_LUASOCKET
  {"socket", luaopen_socket_core},
#endif
#ifdef WITH_LUACRYPTO
  {"crypto", luaopen_crypto},
#endif
#ifdef WITH_CMSGPACK
  {"cmsgpack", luaopen_cmsgpack},
#endif
#ifdef WITH_LUACJSON
  {"cjson", luaopen_cjson},
#endif

#ifdef WITH_LUADBI_SQLITE
  {"sqlite3", luaopen_dbdsqlite3},
#endif
#ifdef WITH_LUADBI_MYSQL
  {"mysql", luaopen_dbdmysql},
#endif
  {NULL, NULL}
};


LUALIB_API void luaL_openlibs (lua_State *L) {
  const luaL_Reg *lib = lualibs;
  for (; lib->func; lib++) {
    lua_pushcfunction(L, lib->func);
    lua_pushstring(L, lib->name);
    lua_call(L, 1, 0);
  }
}

