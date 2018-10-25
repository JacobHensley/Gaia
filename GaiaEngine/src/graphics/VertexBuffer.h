#pragma once
#include "utils/Common.h"
#include "utils/RefCounted.h"
#include "BufferLayout.h"

class VertexBuffer : public RefCounted
{
public:
	VertexBuffer(uint count);
	VertexBuffer(float* data, int count);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

	template<typename T = void>
	inline T* Map()
	{
		return (T*)MapInternal();
	}

	void Unmap();
private:
	void* MapInternal();

	uint m_BufferID;
	BufferLayout m_Layout;
};

typedef Ref<VertexBuffer> VertexBufferRef;