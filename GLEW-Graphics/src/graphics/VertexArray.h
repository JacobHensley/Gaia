#pragma once
#include "Buffer.h"
#include "../Common.h"
#include <vector>
#include "GL\glew.h"
#include "RefCounted.h"

class VertexArray : public RefCounted
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

typedef Ref<VertexArray> VertexArrayRef;