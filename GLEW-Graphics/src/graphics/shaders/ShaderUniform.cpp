#include "ShaderUniform.h"

ShaderUniform::ShaderUniform(const String& name, const String& type, uint count)
	: m_Name(name), m_Count(count), m_Offset(0) {
	m_Type = StringToType(type);
	m_Size = SizeFromType(m_Type) * m_Count;
}


ShaderUniform::~ShaderUniform()
{
}

uint ShaderUniform::SizeFromType(Type type)
{
	if (type == Type::SHADER_INT) return 4;
	else if (type == Type::SHADER_FLOAT) return 4;
	else if (type == Type::SHADER_SAMPLER2D) return 4; //TODO: Can't find the size of sampler2D, so I am using 4 as a place holder
	else if (type == Type::SHADER_MAT4) return 4 * 4 * 4;
	else return NULL;
}

Type ShaderUniform::StringToType(const String& name)
{
	if (name == "int") return Type::SHADER_INT;
	else if (name == "float") return Type::SHADER_FLOAT;
	else if (name == "sampler2D") return Type::SHADER_SAMPLER2D;
	else if (name == "mat4") return Type::SHADER_MAT4;
	else return Type::NONE;
}

String ShaderUniform::StringFromType(Type type)
{
	if (type == Type::SHADER_INT) return "int";
	else if (type == Type::SHADER_FLOAT) return "float";
	else if (type == Type::SHADER_SAMPLER2D) return "sampler2D";
	else if (type == Type::SHADER_MAT4) return "mat4";
	else return "";
}