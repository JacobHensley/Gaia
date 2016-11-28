#pragma once
#include "GL\glew.h"
#include "../Common.h"

class Buffer
{
public:
	Buffer(GLfloat* data, GLsizei count, uint componentCount);
	~Buffer();

	void bind() const;
	void unbind() const;
	inline uint getComponentCount() const { return m_componentCount; }
private:
	uint m_componentCount;
	uint m_bufferID;
};