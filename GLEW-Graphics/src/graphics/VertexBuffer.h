#pragma once
#include "GL/glew.h"
#include "Common.h"
#include "RefCounted.h"
#include "BufferLayout.h"

class VertexBuffer : public RefCounted
{
public:
	VertexBuffer(uint count);
	VertexBuffer(float* data, int count, uint componentCount);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	inline uint GetComponentCount() const { return m_ComponentCount; }
	inline void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

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
	BufferLayout m_Layout;
};

typedef Ref<VertexBuffer> VertexBufferRef;