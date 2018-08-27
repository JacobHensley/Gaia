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

	UniformBuffer m_VSUserUniformBuffer;
	UniformBuffer m_FSUserUniformBuffer;
public:
	Material(Shader* shader);
	~Material();

	template<typename T> 
	void SetValue(const String& name, const T& value)
	{
		//TODO: get offset from uniform declaration
		uint offset = 0;
		//TODO: get right Buffer from uniform declaration
		UniformBuffer& buffer = m_VSUserUniformBuffer;
		memcpy(buffer.buffer + offset, &value, sizeof(T));
	}

	void SetTexture(const String& name, Texture* texture);
private:
	void AllocateStorage();
	void FreeStorage();
};