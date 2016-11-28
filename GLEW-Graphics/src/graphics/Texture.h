#pragma once
#include "../Common.h"

class Texture
{
public:
	Texture(const char* path);
	~Texture();

	void Bind();
	void Unbind();

	inline const char* getPath() { return m_path; }
private:
	uint load();
	uint m_Texture;
	const char* m_path;
};