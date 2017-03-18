#pragma once
#include "../Common.h"
#include "../Resource.h"
#include "RefCounted.h"

class Texture : public RefCounted
{
public:
	Texture(const String& path);
	~Texture();

	void Bind();
	void Unbind();

	inline const String& GetPath() { return m_Path; }
	inline const uint GetTexture() { return m_Texture; }
	static inline Resource::ResourceType GetType() { return Resource::ResourceType::TEXTURE; }
private:
	uint Load();
	uint m_Texture;
	const String& m_Path;
};

typedef Ref<Texture> TextureRef;