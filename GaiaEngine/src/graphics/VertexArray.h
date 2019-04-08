#pragma once

#include "graphics/VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
public:
	void PushVertexBuffer(VertexBuffer* VB);
	void Bind();
	void Unbind();
private:
	uint m_VertexArray;
};

