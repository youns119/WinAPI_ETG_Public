#pragma once

#pragma comment(lib, "msimg32.lib")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

#include <math.h>
#include <time.h>
#include <functional>
#include <assert.h>
#include <thread>

#include "Define.h"
#include "Vec2.h"
#include "Templates.h"

#include "Singleton.h"
#include "AFactory.h"

#include "IObject.h"

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc.lib")

#include <io.h>

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif