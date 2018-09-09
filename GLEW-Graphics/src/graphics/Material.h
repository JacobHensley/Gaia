#pragma once
#include "shaders/Shader.h"

class Material
{
private:
	struct  UniformBuffer
	{
		byte* buffer;
		uint size;

		~UniformBuffer()
		{
			delete[] buffer;
		}
	};
private:
	Shader* m_Shader;
	std::vector<Texture*> m_Textures;
	std::vector<ShaderUniform> m_Uniforms;
	UniformBuffer m_UniformBuffer;
public:
	Material(Shader* shader);
	~Material();

	template<typename T> 
	void SetValue(const String& name, const T& value)
	{
		uint offset = 0;

		for (int i = 0; i < m_Uniforms.size(); i++)
		{
			if (m_Uniforms[i].GetName() == name)
				break;
			offset += m_Uniforms[i].GetSize();
		}

		UniformBuffer& buffer = m_UniformBuffer;
		memcpy(buffer.buffer + offset, &value, sizeof(T));
	}

	void SetTexture(const String& name, Texture* texture);
private:
	void AllocateStorage();
	void FreeStorage();
};