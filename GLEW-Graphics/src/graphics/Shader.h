#pragma once
#include <GL\glew.h>
#include "../Common.h"
#include "../utils/FileUtils.h"
#include <vector>

class Shader
{
public:
	Shader(const String& vertPath, const String& fragPath);
	~Shader();

	void bind();
	void unbind();
	inline uint GetID() const { return m_ShaderID; }
private:
	uint m_ShaderID;
	String m_vertPath, m_fragPath;
	uint load();
};