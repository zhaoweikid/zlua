import os, sys, glob

mysql_home	= '/opt/mysql5'
sqlite_home = '/usr/local'

options = Variables()
options.Add( EnumVariable('module',
                        'module compiled in lua',
						'', [], ignorecase=2) )
modules = ARGUMENTS.get('module', 'all')

cmod = modules.split(',')

libname		= 'zlua'
luaname		= 'zlua'
luacname	= 'zluac'
includes	= ['include', '.', 'module']
libs		= ['z','m','dl','rt']
libpath		= ['.', '/usr/local/lib']
ldflags		= '-pthread'

defs = ['LUA_ANSI', 'LUASOCKET_DEBUG']

lua_files  = ['src/lua.c']
luac_files = ['src/luac.c', 'src/print.c']
obj_files  = [ f for f in glob.glob('src/*.c') if f not in lua_files and f not in luac_files]
static_files = []


if cmod[0] == 'all':
	cmod = ['socket','cmsgpack','crypto','dbd','cjson']

print cmod
if 'socket' in cmod:
	socket_win_files = ['module/luasocket/wsocket.c']
	socket_files = [f for f in glob.glob('module/luasocket/*.c') if f not in socket_win_files]
	obj_files += socket_files
	defs.append('WITH_LUASOCKET')

if 'crypto' in cmod:
	crypto_files = [f for f in glob.glob('module/luacrypto/*.c')]
	obj_files += crypto_files
	obj_files.append('/usr/local/ssl/lib/libcrypto.a')

	defs += ['WITH_LUACRYPTO','OPENSSL_EXTERNAL_INITIALIZATION']

if 'cmsgpack' in cmod:
	msgpack_files = [f for f in glob.glob('module/cmsgpack/*.c')]
	obj_files += msgpack_files
	
	defs.append('WITH_CMSGPACK')

if 'cjson' in cmod:
	files = [f for f in glob.glob('module/cjson/*.c')]
	obj_files += files
	
	defs += ['WITH_LUACJSON','ENABLE_CJSON_GLOBAL']

if 'dbd' in cmod:
	files = [f for f in glob.glob('module/dbd/*.c')]
	
	sqlite_lib = os.path.join(sqlite_home, 'lib/libsqlite3.a')

	oldlen = len(obj_files)

	if os.path.isfile(sqlite_lib):
		files2 = [f for f in glob.glob('module/dbd/sqlite3/*.c')]
		obj_files += files2
		obj_files.append(sqlite_lib)

	if os.path.isdir(mysql_home):
		files2 = [f for f in glob.glob('module/dbd/mysql/*.c')]
		obj_files += files2
		mysql_lib = os.path.join(mysql_home, 'lib/libmysqlclient.a')
		obj_files.append(mysql_lib)

		includes.append(os.path.join(mysql_home, 'include'))
		ldflags += ' -lstdc++' 


	if len(obj_files) > oldlen:
		obj_files += files
	
	defs.append('WITH_LUADBI')

env = Environment(CCFLAGS='-O2 -Wall -pthread', 
				CPPDEFINES=defs, CPPPATH=includes, 
				LIBPATH=libpath, LIBS=libs, LINKFLAGS=ldflags)

env.StaticLibrary(libname, obj_files)
env.Program(luaname, obj_files+lua_files)
env.Program(luacname, obj_files+luac_files)

