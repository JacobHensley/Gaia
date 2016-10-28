#include "GLError.h"
#include <gl\glew.h>
#include <iostream>

unsigned int GLCheckError()
{
	return glGetError();
}

bool GLLogCall(const char* function, const char* file, int line)
{
	unsigned int error = GLCheckError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
