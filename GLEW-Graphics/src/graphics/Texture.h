#pragma once
#include "../Common.h"

class Texture
{
public:
	Texture(const char* path);
	const char* m_path;
private:
	void load();
};