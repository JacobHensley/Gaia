#include "FontManager.h"

FontManager::FontManager()
{
	Init();
}

FontManager::~FontManager()
{
}

FT_Face FontManager::LoadFace(const String& path)
{
	FT_Face face;
	int error = FT_New_Face(m_FT, path.c_str(), 0, &face);

	if (error == FT_Err_Unknown_File_Format)
		std::cout << "Failed to load font file, format may be unsupported" << std::endl;
	else if (error)
		std::cout << "Font file could not be open or read, error code: " + error << std::endl;

	return face;
}

void FontManager::Init()
{
	int error = FT_Init_FreeType(&m_FT);
	if (error)
	{
		std::cout << "Failed to initialize FreeType lib, error code: " + error << std::endl;
	}
}
