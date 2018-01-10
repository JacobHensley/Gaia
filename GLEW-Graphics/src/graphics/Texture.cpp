#include "Texture.h"
#include "stb_image.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Texture::Texture(const String& path, TextureParameters parameters)
	:	m_Path(path), m_Parameters(parameters)
{
	m_Texture = LoadFromFile();
}

Texture::Texture(uint width, uint height, TextureParameters parameters)
	:	m_Width(width), m_Height(height), m_Parameters(parameters)
{
	m_Texture = Load(nullptr, m_Width, m_Height);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_Texture));
}

uint Texture::LoadFromFile()
{
	int width, height, bpc;
	byte* data = stbi_load(m_Path.c_str(), &width, &height, &bpc, 0);
	ASSERT(data);

	uint texture = Load(data, width, height);

	m_Width = width;
	m_Height = height;

	stbi_image_free(data);
	return texture;
}


static byte* AlignData(byte* data, uint size) 
{
	byte* buffer = new byte[size * 4];
	memset(buffer, 0, size * 4);
	for (int i = 0; i < size; i++) {
		buffer[i * 4] = data[i];
	}

	return buffer;
}

uint Texture::Load(byte* data, uint width, uint height)
{
	uint texture;

	GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1))

	GLCall(glGenTextures(1, &texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatToGL(m_Parameters.format), width, height, 0, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGL(m_Parameters.filter)));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGL(m_Parameters.filter)));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(m_Parameters.wrap)));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(m_Parameters.wrap)));

	return texture;
}

void Texture::SetData(byte* data, uint size)
{
	Bind();
	ASSERT(size == m_Width * m_Height * GetStrideFromFormat(m_Parameters.format));
	byte* alignedData = AlignData(data, size);
	GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, data));
	Unbind();
}

byte Texture::GetStrideFromFormat(TextureFormat format)
{
	switch (format)
	{
		case TextureFormat::RED:				return 1;
		case TextureFormat::RGB:				return 3;
		case TextureFormat::RGBA:				return 4;
		case TextureFormat::LUMINANCE_ALPHA:	return 4;
	}
	return 0;
}

uint Texture::TextureFormatToGL(TextureFormat format)
{
	switch (format)
	{
		case TextureFormat::RGBA:				return GL_RGBA;
		case TextureFormat::RGB:				return GL_RGB;
		case TextureFormat::RED:				return GL_RED;
		case TextureFormat::LUMINANCE:			return GL_LUMINANCE;
		case TextureFormat::LUMINANCE_ALPHA:	return GL_LUMINANCE_ALPHA;
	}
	return 0;
}

uint Texture::TextureWrapToGL(TextureWrap wrap)
{
	switch (wrap)
	{
		case TextureWrap::CLAMP:			return GL_CLAMP;
		case TextureWrap::CLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
		case TextureWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case TextureWrap::REPEAT:			return GL_REPEAT;
		case TextureWrap::MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
	}
	return 0;
}

uint Texture::TextureFilterToGL(TextureFilter filter)
{
	switch (filter)
	{
		case TextureFilter::LINEAR:			return GL_LINEAR;
		case TextureFilter::NEAREST:		return GL_NEAREST;
	}
	return 0;
}

void Texture::Bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}