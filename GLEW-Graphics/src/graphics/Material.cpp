#include "Material.h"

Material::Material(Shader* shader)
	: m_Shader(shader)
{
	AllocateStorage();
	SetValue("test", 5);
}

Material::~Material()
{
}

void Material::AllocateStorage()
{
	//TODO: Get uniform declaration from shader
	uint vsUniformSize = 0;
	uint fsUniformSize = 0;

	m_VSUserUniformBuffer.buffer = new byte[vsUniformSize];
	m_VSUserUniformBuffer.size = vsUniformSize;

	m_FSUserUniformBuffer.buffer = new byte[fsUniformSize];
	m_FSUserUniformBuffer.size = fsUniformSize;

	//TODO: get texture count from shader
	uint TextureCount = 1;
	m_Textures.resize(TextureCount);
}

void Material::FreeStorage()
{

}

void Material::SetTexture(const String& name, Texture* texture)
{
	//TODO: get index by name from declaration
	uint index = 0;
	m_Textures[index] = texture;
}

