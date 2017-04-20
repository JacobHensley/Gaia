#pragma once
#include "../Common.h"
#include "RefCounted.h"

class IndexBuffer : public RefCounted
{
public:
	IndexBuffer(uint* data, uint count);
	~IndexBuffer();

	void Draw() const;
	void Draw(uint count) const;
	void Bind() const;
	void Unbind() const;
private:
	uint m_BufferID;
	uint m_Count;
};

typedef Ref<IndexBuffer> IndexBufferRef;