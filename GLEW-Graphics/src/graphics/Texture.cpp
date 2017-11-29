#include "Texture.h"
#include "stb_image.h"
#include "GLFW/glfw3.h"

Texture::Texture(const String& path)
	:	m_Path(path) 
{
	m_Texture = Load();
}

Texture::Texture(uint width, uint height)
	:	m_Width(width), m_Height(height)	
{
	uint texture;
	GLCall(glGenTextures(1, &texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	m_Texture = texture;
}


Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_Texture));
}

uint Texture::Load()
{
	int width, height, bpc;
	byte* data = stbi_load(m_Path.c_str(), &width, &height, &bpc, 0);
	ASSERT(data);

	uint texture;
	GLCall(glGenTextures(1, &texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	m_Width = width;
	m_Height = height;

	stbi_image_free(data);
	return texture;
}

void Texture::Bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
}


void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::SetData(byte* data, uint size)
{
	Bind();
	ASSERT(size == m_Width * m_Height * 1); //TODO: Change to work per format
	GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RED, GL_UNSIGNED_BYTE, data));
	Unbind();
}
