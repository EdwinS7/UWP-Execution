#include <windows.h>
#include <cstdint>
#include <sstream>
#include <iomanip> 
#include <fstream>
#include <random>
#include <thread>
#include <vector>
#include <string>
#include <format>
#include <array>

#include "third-party/xorstr.hpp"
#include "third-party/ZStd/inc/zstd.h"
#include "third-party/XXHash/src/xxhash.h"
#include "third-party/MinHook/MinHook.h"

#include "third-party/LuaU/inc/lualib.h"
#include "third-party/LuaU/src/Compiler.h"
#include "third-party/LuaU/src/BytecodeBuilder.h"
#include "third-party/LuaU/src/luacode.h"

#define ENVIORNMENT_NAME xorstr_( "UntitledProject" )

#include "include/utilities/defines.hpp"
#include "include/utilities/utilities.hpp"
#include "include/memory/memory.hpp"
#include "include/hooks/hooks.hpp"
#include "include/serializer/serializer.hpp"
#include "include/scheduler/scheduler.hpp"

//@note: used for communication between external client and internal (this).
#include "include/bridge/bridge.hpp"

#include "include/context/context.hpp"