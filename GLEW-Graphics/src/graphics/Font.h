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
	Texture* m_AtlasTexture;
	
	ftgl::texture_atlas_t* m_FTAtlas;
	ftgl::texture_font_t* m_FTFont;
public:
	Font(const String& name, const String& filePath, float size);

	void UpdateAtlasTexture();

	inline const String& GetName() const { return m_Name; }
	inline float GetSize() const { return m_Size; }

	inline Texture* GetAtlasTexture() const { return m_AtlasTexture; }
	inline ftgl::texture_atlas_t* GetAtlas() const { return m_FTAtlas; }
	inline ftgl::texture_font_t* GetFont() const { return m_FTFont; }
};