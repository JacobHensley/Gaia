#pragma once
#include "../Common.h"

class Texture
{
public:
	Texture(const char* path);

	inline const char* getPath() { return m_path; }
private:
	void load();
	const char* m_path;
};