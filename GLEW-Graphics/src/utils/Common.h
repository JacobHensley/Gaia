#pragma once

#include <string>
#include <iostream>
#include "GLError.h"
#include <unordered_map>

typedef std::string String;
typedef unsigned int uint;
typedef unsigned char byte;

#ifdef _DEBUG
#define ASSERT(condition, message) if (!(condition)) { \
	std::cout << "Assertion Failed!" << std::endl; \
	std::cout << "File: " << __FILE__ << ", Line: " << __LINE__ << std::endl; \
	std::cout << "Error: " << message << std::endl; \
	std::cout << "Condition: " << #condition << std::endl; \
	__debugbreak(); \
}
#else
#define ASSERT(condition) condition
#endif