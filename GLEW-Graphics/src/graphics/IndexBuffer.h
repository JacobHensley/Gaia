#pragma once
#include "GL\glew.h"
#include "../Common.h"

class IndexBuffer
{
public:
	IndexBuffer(uint* data, GLsizei count);

	void draw() const;
	void bind() const;
	void unbind() const;
private:
	uint m_bufferID;
	uint m_count;
};