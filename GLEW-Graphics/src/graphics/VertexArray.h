#pragma once
#include "Buffer.h"
#include "../Common.h"
#include <vector>
#include "GL\glew.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(Buffer* buffer, uint index);

	void Bind() const;
	void Unbind() const;
private:
	uint m_ArrayID;
	std::vector<Buffer*> m_Buffers;
};