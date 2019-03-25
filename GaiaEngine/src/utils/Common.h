#pragma once

#include <string>
#include <iostream>
#include "GLError.h"
#include <unordered_map>

typedef std::string String;
typedef unsigned int uint;
typedef unsigned char byte;

#ifdef GA_PLATFORM_WINDOWS
	#ifdef GA_BUILD_DLL
		#define GAIA_API __declspec(dllexport)
	#else
		#define GAIA_API __declspec(dllimport)
	#endif
#endif

#ifdef _DEBUG
#define ASSERT(condition) if (!(condition)) { \
	std::cout << "Assertion Failed!" << std::endl; \
	std::cout << "File: " << __FILE__ << ", Line: " << __LINE__ << std::endl; \
	std::cout << "Condition: " << #condition << std::endl; \
	__debugbreak(); \
}
#else
#define ASSERT(condition) condition
#endif