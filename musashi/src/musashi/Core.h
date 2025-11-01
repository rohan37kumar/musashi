//currently has all the definitions

#pragma once

#ifdef MSSHI_PLATFORM_WINDOWS
	#if MSSHI_DLL_BUILD
		#ifdef MSSHI_BUILD_DLL
			#define MSSHI_API __declspec(dllexport)	
		#else
			#define MSSHI_API __declspec(dllimport)
		#endif //to declare export and import functions between the engind and the sandbox
		//dllexport and dllimport are signals for when linking the dll file to the sandbox application, what to export form here and what to import there.
	#else
		#define MSSHI_API
	#endif
#else
	#error Only Windows is supported for now!
#endif

#ifdef MSSHI_DEBUG
	#define MSSHI_ENABLE_ASSERTS
#endif

//useful macros for verifying assumptions at runtime
#ifdef MSSHI_ENABLE_ASSERTS
	#define MSSHI_ASSERT(x, ...) { if(!(x)) { MSSHI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MSSHI_CORE_ASSERT(x, ...) { if(!(x)) { MSSHI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	//__debugbreak() triggers a breakpoint in the debugger
#else
	#define MSSHI_ASSERT(x, ...)
	#define MSSHI_CORE_ASSERT(x, ...)
#endif 

#define BIT(x) (1 << x) //simple macro for number to bit conversion, 0 = 0001, 1 = 0010, 2 = 0100...

#define MSSHI_BIND_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)
//binding event fns into a callable
