#pragma once
#include "GaPCH.h"
#include "utils/Common.h"
#include "Font.h"
#include "vector.h"

class FontManager
{
public:
	FontManager();

	static void LoadFont(Font* font);
	static Font* GetFont(const String& name, int size);
	static Font* GetFont(const String& name);
	static Font* GetFont(int size);
private:
	static std::vector<Font*> s_Fonts;
};