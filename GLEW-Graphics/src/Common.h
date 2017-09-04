#pragma once

#include <string>
#include <iostream>
#include "GLError.h"
#include <unordered_map>

typedef std::string String;
typedef unsigned int uint;
typedef unsigned char byte;

#ifdef _DEBUG
#define ASSERT(condition) if (!(condition)) { \
	std::cout << "Assert Failed!" << std::endl; \
	std::cout << "Condition: " << #condition << std::endl; \
	__debugbreak(); \
}
#else
#define ASSERT(condition) condition
#endif
