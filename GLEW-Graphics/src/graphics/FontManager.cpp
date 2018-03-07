#include "FontManager.h"

std::vector<Font*> FontManager::s_Fonts;

FontManager::FontManager()
{
}

void FontManager::LoadFont(Font* font)
{
	for (int i = 0;i < s_Fonts.size();i++)
	{
		if (s_Fonts[i] == font)
			return;
	}

	s_Fonts.push_back(font);
}

Font* FontManager::GetFont(const String& name, int size)
{
	for (int i = 0; i < s_Fonts.size(); i++)
	{
		Font* font = s_Fonts[i];
		if (font->GetName() == name && font->GetSize() == size)
			return s_Fonts[i];
	}
	return nullptr;
}

Font* FontManager::GetFont(const String& name)
{
	for (int i = 0; i < s_Fonts.size(); i++)
	{
		Font* font = s_Fonts[i];
		if (font->GetName() == name)
			return s_Fonts[i];
	}
	return nullptr;
}

Font* FontManager::GetFont(int size)
{
	for (int i = 0; i < s_Fonts.size(); i++)
	{
		Font* font = s_Fonts[i];
		if (font->GetSize() == size)
			return s_Fonts[i];
	}
	return nullptr;
}