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

	void addBuffer(Buffer* buffer, uint index);

	void bind() const;
	void unbind() const;
private:
	uint m_arrayID;
	std::vector<Buffer*> m_buffers;
};