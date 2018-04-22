#pragma once
#include "../utils/Common.h"
#include "../utils/Resource.h"
#include "utils/RefCounted.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class Texture : public RefCounted
{

public:
	enum class TextureWrap
	{
		NONE = 0,
		REPEAT,
		CLAMP,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum class TextureFilter
	{
		NONE = 0,
		LINEAR,
		NEAREST
	};

	enum class TextureFormat
	{
		NONE = 0,
		RED,
		RGB,
		RGBA,
		LUMINANCE,
		LUMINANCE_ALPHA
	};

	struct TextureParameters
	{
		TextureFormat format;
		TextureFilter filter;
		TextureWrap wrap;

		TextureParameters()
		{
			format = TextureFormat::RGBA;
			filter = TextureFilter::LINEAR;
			wrap = TextureWrap::CLAMP;
		}

		TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap)
			: format(format), filter(filter), wrap(wrap)
		{
		}

		TextureParameters(TextureFormat format)
			: format(format), filter(TextureFilter::LINEAR), wrap(TextureWrap::CLAMP)
		{
		}
	};

public:
	Texture(uint width, uint height, TextureParameters parameters = TextureParameters());
	Texture(const String& path, TextureParameters parameters = TextureParameters());
	~Texture();

	void Bind();
	void Unbind();

	void SetData(byte* data, uint size);
	static byte GetStrideFromFormat(TextureFormat format);

	inline const TextureParameters& GetParams() const { return m_Parameters; };
	inline const String& GetPath() const { return m_Path; }
	inline const uint GetTexture() const { return m_Texture; }

	inline const uint GetWidth() const { return m_Width; }
	inline const uint GetHeight() const { return m_Height; }

	static inline Resource::ResourceType GetType() { return Resource::ResourceType::TEXTURE; }

private:
	uint Load(byte* data, uint width, uint height);
	uint LoadFromFile();

	static uint TextureFormatToGL(TextureFormat format);
	static uint TextureWrapToGL(TextureWrap wrap);
	static uint TextureFilterToGL(TextureFilter filter);

	uint m_Texture;
	uint m_Width, m_Height;
	TextureParameters m_Parameters;
	String m_Path;
};

typedef Ref<Texture> TextureRef;