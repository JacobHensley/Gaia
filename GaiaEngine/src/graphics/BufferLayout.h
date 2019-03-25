#pragma once
#include "utils/Common.h"
#include "math/vec3.h"

#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406

class GAIA_API BufferLayout
{
private:
	struct GAIA_API BufferElement
	{
		String name;
		uint type;
		byte count;
		byte size;
		uint offset;
	};
private:
	std::vector<BufferElement> m_Elements;
	uint m_Stride;
public:
	BufferLayout();
	
	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	inline uint GetStride() const { return m_Stride; }

	template<typename T>
	void Push(const String& name)
	{
		static_assert(false, "Unknown Type!");
	}

	template<> void Push<float>(const String& name);
	template<> void Push<int>(const String& name);
	template<> void Push<uint>(const String& name);
	template<> void Push<byte>(const String& name);

	template<> void Push<vec2>(const String& name);
	template<> void Push<vec3>(const String& name);
	template<> void Push<vec4>(const String& name);
private:
	void PushInternal(const String& name, uint type, byte count, byte size);
};

template<>
void BufferLayout::Push<float>(const String& name)
{
	PushInternal(name, GL_FLOAT, 1, sizeof(float));
}

template<>
void BufferLayout::Push<int>(const String& name)
{
	PushInternal(name, GL_INT, 1, sizeof(int));
}

template<>
void BufferLayout::Push<uint>(const String& name)
{
	PushInternal(name, GL_UNSIGNED_INT, 1, sizeof(uint));
}

template<>
void BufferLayout::Push<byte>(const String& name)
{
	PushInternal(name, GL_BYTE, 1, sizeof(byte));
}

template<>
void BufferLayout::Push<vec2>(const String& name)
{
	PushInternal(name, GL_FLOAT, 2, sizeof(float));
}

template<>
void BufferLayout::Push<vec3>(const String& name)
{
	PushInternal(name, GL_FLOAT, 3, sizeof(float));
}

template<>
void BufferLayout::Push<vec4>(const String& name)
{
	PushInternal(name, GL_FLOAT, 4, sizeof(float));
}

#undef GL_BYTE
#undef GL_UNSIGNED_BYTE 
#undef GL_SHORT 
#undef GL_UNSIGNED_SHORT 
#undef GL_INT 
#undef GL_UNSIGNED_INT 
#undef GL_FLOAT 