#pragma once

unsigned int GLCheckError();
bool GLLogCall(const char* function, const char* file, int line);

#define GLCall(x) GLCheckError();\
	x;\
	if (!GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();