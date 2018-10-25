#include "BufferLayout.h"

BufferLayout::BufferLayout()
	: m_Stride(0)
{
}


void BufferLayout::PushInternal(const String& name, uint type, byte count, byte size)
{
	byte index = 0;
	byte offset = 0;
	if (m_Elements.size() > 0)
	{
		const BufferElement& prev = m_Elements.back();
		offset = prev.offset + prev.size * prev.count;
	}
	m_Elements.push_back({ name, type, count, size, offset });
	m_Stride += count * size;
}