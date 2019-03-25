#pragma once
#include "utils/Common.h"
#include "utils/RefCounted.h"

class GAIA_API IndexBuffer : public RefCounted
{
public:
	IndexBuffer(const uint* data, uint count);
	~IndexBuffer();

	void Draw() const;
	void Draw(uint count) const;
	void DrawLine(uint count) const;
	void Bind() const;
	void Unbind() const;
private:
	uint m_BufferID;
	uint m_Count;
};

typedef Ref<IndexBuffer> IndexBufferRef;