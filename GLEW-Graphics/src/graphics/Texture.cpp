#include "Texture.h"
#include "stb_image.h"
#include "GLFW\glfw3.h"

Texture::Texture(const String& path)
	:	m_Path(path) {
	m_Texture = Load();
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
