#pragma once
#include "../Common.h"
#include "../Resource.h"
class Texture
{
public:
	Texture(const String& path);
	~Texture();

	void Bind();
	void Unbind();

	inline const String& GetPath() { return m_Path; }
	static inline Resource::ResourceType GetType() { return Resource::ResourceType::TEXTURE; }
private:
	uint Load();
	uint m_Texture;
	const String& m_Path;
};