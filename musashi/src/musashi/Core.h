//currently has all the definitions

#pragma once

#ifdef MSSHI_PLATFORM_WINDOWS
	#ifdef MSSHI_BUILD_DLL
		#define MSSHI_API __declspec(dllexport)	
	#else
		#define MSSHI_API __declspec(dllimport)
	#endif //to declare export and import functions between the engind and the sandbox
	//dllexport and dllimport are signals for when linking the dll file to the sandbox application, what to export form here and what to import there.
#else
	#error Only Windows is supported for now!
#endif

#define BIT(x) (1 << x) //simple macro for number to bit conversion, 0 = 0001, 1 = 0010, 2 = 0100...
