#pragma once
#include "../Common.h"
#include "../Resource.h"
#include "RefCounted.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class Texture : public RefCounted
{
public:
	Texture(uint width, uint height);
	Texture(const String& path);
	~Texture();

	void Bind();
	void Unbind();

	void SetData(byte* data, uint size);

	inline const String& GetPath() const { return m_Path; }
	inline const uint GetTexture() const { return m_Texture; }

	static inline Resource::ResourceType GetType() { return Resource::ResourceType::TEXTURE; }
private:
	uint Load();
	uint m_Texture;
	String m_Path;
	uint m_Width, m_Height;
};

typedef Ref<Texture> TextureRef;