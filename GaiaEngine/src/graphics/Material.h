#pragma once
#include "shaders/Shader.h"

class GAIA_API Material
{
private:
	struct GAIA_API UniformBuffer
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
	std::vector<ShaderUniform*> m_Uniforms;
	UniformBuffer m_UniformBuffer;
public:
	Material(Shader* shader);
	~Material();

	template<typename T> 
	void SetValue(const String& name, const T& value)
	{
		for (int i = 0; i < m_Uniforms.size(); i++)
		{
			if (m_Uniforms[i].GetName() == name) //TODO: This should be moved into a map.
			{
				UniformBuffer& buffer = m_UniformBuffer;
				memcpy(buffer.buffer + m_Uniforms[i]->GetOffset(), &value, sizeof(T));
				break;
			}
		}
	}

	void SetTexture(const String& name, Texture* texture);
private:
	void AllocateStorage();
	void FreeStorage();
};