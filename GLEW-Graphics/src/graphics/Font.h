#pragma once
#include "Common.h"
#include "Texture.h"


#include "freetype-gl.h"

class Font 
{
private:
	String m_Name;
	String m_FilePath;
	float m_Size;
	Texture* m_Texture;
	
	ftgl::texture_atlas_t* m_FTAtlas;
	ftgl::texture_font_t* m_FTFont;
public:
	Font(const String& filePath, float size);

	inline ftgl::texture_atlas_t* GetAtlas() const { return m_FTAtlas; }
	inline ftgl::texture_font_t* GetFont() const { return m_FTFont; }
};