#pragma once

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif


//standard stuff
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>


#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

#include "musashi/Log.h"

#ifdef MSSHI_PLATFORM_WINDOWS
	#include <Windows.h>
#endif //if on windows platform
