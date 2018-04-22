#include "Shader.h"
#include <GL/glew.h>

Shader::Shader(const String& vertPath, const String& fragPath)
	:	m_VertPath(vertPath), m_FragPath(fragPath)	
{
	m_ShaderID = Load();
	ASSERT(m_ShaderID);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_ShaderID));
}

uint Shader::Load()
{
	GLCall(uint program = glCreateProgram());
	GLCall(uint vertex = glCreateShader(GL_VERTEX_SHADER));
	GLCall(uint fragment = glCreateShader(GL_FRAGMENT_SHADER));

	String vertexSrc = ReadFile(m_VertPath);
	String fragSrc = ReadFile(m_FragPath);

	const char* vs = vertexSrc.c_str();
	GLCall(glShaderSource(vertex, 1, &vs, NULL));
	GLCall(glCompileShader(vertex));

	int compileResult;
	GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &compileResult));

	if (compileResult == GL_FALSE) 
	{
		int length;
		GLCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length));
		std::vector<char> error(length);
		GLCall(glGetShaderInfoLog(vertex, length, &length, &error[0]));

		std::cout << &error[0] << std::endl;
		std::cout << "Vertex shader failed to compile" << std::endl;
		GLCall(glDeleteShader(vertex));
		return 0;
	}

	const char* fs = fragSrc.c_str();
	GLCall(glShaderSource(fragment, 1, &fs, NULL));
	GLCall(glCompileShader(fragment));

	GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &compileResult));

	if (compileResult == GL_FALSE) 
	{
		int length;
		GLCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length));
		std::vector<char> error(length);
		GLCall(glGetShaderInfoLog(fragment, length, &length, &error[0]));

		std::cout << &error[0] << std::endl;
		std::cout << "Fragment shader failed to compile" << std::endl;
		GLCall(glDeleteShader(fragment));
		return 0;
	}

	GLCall(glAttachShader(program, vertex));
	GLCall(glAttachShader(program, fragment));

	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));

	return program;
}

void Shader::Bind()
{
	GLCall(glUseProgram(m_ShaderID));
}

void Shader::Unbind() 
{
	GLCall(glUseProgram(0));
}

void Shader::SetTextureIDs(const String& name)
{
	int texIDs[32];
	for (int i = 0;i< 32;i++) 
	{
		texIDs[i] = i;
	}

	Bind();
	SetUniform1iv(name, texIDs, 32);
	Unbind();
}

int Shader::GetUniformLocation(const String& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_ShaderID, name.c_str()));
//	ASSERT(location != -1);

	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniform1i(const String& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(const String& name, int* value, int count)
{
	GLCall(glUniform1iv(GetUniformLocation(name), count, value));
}

void Shader::SetUniform1f(const String& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const String& name, const vec2& vec)
{
	GLCall(glUniform2f(GetUniformLocation(name), vec.x, vec.y));
}

void Shader::SetUniform3f(const String& name, const vec3& vec)
{
	GLCall(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
}

void Shader::SetUniformVec4(const String& name, const vec4& vec)
{
	SetUniform4f(name, vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniform4f(const String& name, float x, float y, float z, float w)
{
	GLCall(glUniform4f(GetUniformLocation(name), x, y, z, w));
}

void Shader::SetUniformMat4(const String& name, const mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, matrix.elements));
}