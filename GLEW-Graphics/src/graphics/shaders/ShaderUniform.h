#pragma once
#include "utils/Common.h"

enum Type
{
	NONE = 0, SHADER_INT = 1, SHADER_FLOAT = 2, SHADER_SAMPLER2D = 3, SHADER_MAT4 = 4
};

class ShaderUniform
{
public:
	ShaderUniform(const String& name, const String& type, uint count);
	~ShaderUniform();

	uint SizeFromType(Type type);

	Type StringToType(const String& name);
	String StringFromType(Type type);

	inline const String& GetName() { return m_Name; }
	inline const Type GetType() { return m_Type; }
	inline const uint GetCount() { return m_Count; }
	inline const uint GetSize() { return m_Size; }
	inline const uint GetOffset() { return m_Offset; }

private:
	String m_Name;
	Type m_Type;
	uint m_Count;
	uint m_Size;
	uint m_Offset;
};

