#pragma once
#include <GL\glew.h>
#include "../Common.h"
#include "../utils/FileUtils.h"
#include <vector>
#include "../math/math.h" 
#include <unordered_map>
#include "../Resource.h"

class Shader
{
public:
	Shader(const String& vertPath, const String& fragPath);
	~Shader();

	void Bind();
	void Unbind();

	int GetUniformLocation(const String& name);

	void SetUniform1i(const String& name, int value);
	void SetUniform1f(const String& name, float value);
	void SetUniform2f(const String& name, const vec2& vec);
	void SetUniform3f(const String& name, const vec3& vec);
	void SetUniformVec4(const String& name, const vec4& vec);

	void SetUniform4f(const String& name, float x, float y, float z, float w);
	void SetUniformMat4(const String& name, const mat4& matrix);

	inline uint GetID() const { return m_ShaderID; }
	static inline Resource::ResourceType GetType() { return Resource::ResourceType::SHADER; }
private:
	uint m_ShaderID;
	String m_VertPath, m_FragPath;
	uint Load();
	std::unordered_map<String, int> m_UniformLocationCache;
};