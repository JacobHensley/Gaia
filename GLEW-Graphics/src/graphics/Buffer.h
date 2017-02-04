#pragma once
#include "GL\glew.h"
#include "../Common.h"

class Buffer
{
public:
	Buffer(uint count);
	Buffer(GLfloat* data, GLsizei count, uint componentCount);
	~Buffer();

	void Bind() const;
	void Unbind() const;
	inline uint GetComponentCount() const { return m_ComponentCount; }

	template<typename T = void>
	inline T* Map()
	{
		GLCall(T* result = (T*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		return result;
	}

	inline void Unmap() 
	{
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
	}
private:
	uint m_ComponentCount;
	uint m_BufferID;
};