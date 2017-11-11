#pragma once
#include "Common.h"
#include "graphics/Texture.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class FontManager
{
public:
	FontManager();
	~FontManager();

	static void Init();

	static FT_Bitmap& GetBitmap(const String& name, int size, char code);
	static FT_Face& LoadFace(const String& name, const String& path);
	static FT_Face& GetFace(const String& name);

	static void WriteText(const String& text, const String& name, int size);

	typedef FT_Library FTLib;
	typedef std::unordered_map<String, FT_Face> FaceMap;
private:
	static FTLib s_FTLib;
	static FaceMap s_FaceMap;
};