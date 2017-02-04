#pragma once
#include "GL\glew.h"
#include "../Common.h"

class IndexBuffer
{
public:
	IndexBuffer(uint* data, GLsizei count);
	~IndexBuffer();

	void Draw() const;
	void Draw(uint count) const;
	void Bind() const;
	void Unbind() const;
private:
	uint m_BufferID;
	uint m_Count;
};