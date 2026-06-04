#pragma once

#ifdef DARK_WINDOWS_BUILD
	#ifdef DARK_BUILD_DLL
		#define DARK_API __declspec(dllexport)
	#else
		#define DARK_API __declspec(dllimport)
	#endif
#else
	#error DARK ENGINE IS ONLY SUPPORTED FOR WINDOWS!
#endif