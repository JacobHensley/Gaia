#include "Shader.h"

Shader::Shader(const String& vertPath, const String& fragPath)
	:	m_vertPath(vertPath), m_fragPath(fragPath)	{
	m_ShaderID = load();
}

Shader::~Shader()
{
}

uint Shader::load()
{
	uint program = glCreateProgram();
	uint vertex = glCreateShader(GL_VERTEX_SHADER);
	uint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	String vertexSrc = readFile(m_vertPath);
	String fragSrc = readFile(m_fragPath);

	const char* vs = vertexSrc.c_str();
	glShaderSource(vertex, 1, &vs, NULL);
	glCompileShader(vertex);

	int compileResult;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		int length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);

		std::cout << &error[0] << std::endl;
		std::cout << "Vertex shader failed to compile" << std::endl;
		glDeleteShader(vertex);
		return 0;
	}

	const char* fs = fragSrc.c_str();
	glShaderSource(fragment, 1, &fs, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		int length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);

		std::cout << &error[0] << std::endl;
		std::cout << "Fragment shader failed to compile" << std::endl;
		glDeleteShader(fragment);
		return 0;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

void Shader::bind()
{
	glUseProgram(m_ShaderID);
}

void Shader::unbind()
{
	glUseProgram(0);
}