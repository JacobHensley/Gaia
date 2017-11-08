#pragma once
#include "Common.h"
#include "graphics/Texture.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class FontManager
{
private:
	FT_Library m_FT;
public:
	FontManager();
	~FontManager();

	FT_Face LoadFace(const String& path);
	inline void SetPixelSize(FT_Face face, int width, int height) { FT_Set_Pixel_Sizes(face, width, height); };
private:
	void Init();
};