#include "Material.h"

Material::Material(Shader* shader)
	: m_Shader(shader)
{
	m_Uniforms = m_Shader->GetUniforms();
	AllocateStorage();
}

Material::~Material()
{
}

void Material::AllocateStorage()
{
	uint uniformBufferSize = 0;

	for (int i = 0; i < m_Uniforms.size(); i++)
	{
		uniformBufferSize += m_Uniforms[i].GetSize();
	}

	m_UniformBuffer.buffer = new byte[uniformBufferSize];
	m_UniformBuffer.size = uniformBufferSize;

	//TODO: get texture count from shader
	uint textureCount = 1;
	m_Textures.resize(textureCount);
}

void Material::FreeStorage()
{

}

void Material::SetTexture(const String& name, Texture* texture)
{
	uint index = 0;

	for (int i = 0; i < m_Uniforms.size(); i++)
	{
		if (m_Uniforms[i].GetName() == name)
		{
			index = i;
			break;
		}
	}

	m_Textures[index] = texture;
}

