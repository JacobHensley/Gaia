#include "FontManager.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

FontManager::FTLib FontManager::s_FTLib;
FontManager::FaceMap FontManager::s_FaceMap;

FontManager::FontManager()
{
	Init();
}

FontManager::~FontManager()
{
}

FT_Bitmap& FontManager::GetBitmap(const String& name, int size, char code)
{
	FT_Face face = GetFace(name);

	uint index = FT_Get_Char_Index(face, code);
	FT_Set_Char_Size(face, 0, size * 64, 72, 72);

	int error = FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);
	ASSERT(error == FT_Err_Ok);

	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	ASSERT(error == FT_Err_Ok);

	return face->glyph->bitmap;
}

FT_Face& FontManager::LoadFace(const String& name, const String& path)
{
	FT_Face face;
	int error = FT_New_Face(s_FTLib, path.c_str(), 0, &face);
	ASSERT(error == FT_Err_Ok);
	s_FaceMap[name] = face;
	return s_FaceMap[name];
}

FT_Face& FontManager::GetFace(const String& name)
{
	return s_FaceMap[name];
}

Texture* FontManager::GetTexture(const String& font, char character, int size)
{
	FT_Bitmap bitmap = GetBitmap(font, size, character);
	Texture* texture = new Texture(bitmap.pitch, bitmap.rows, Texture::TextureFormat::RED);
	texture->SetData(bitmap.buffer, bitmap.pitch * bitmap.rows);
	return texture;
}

void FontManager::WriteText(const String& text, const String& name, int size)
{
	for (int i = 0; i < text.size(); i++)
	{
		FT_Bitmap bitmap = GetBitmap(name, size, text.at(i));
		if (text.at(i) != ' ')
		{
			for (int y = 0; y < bitmap.rows; y++)
			{
				for (int x = 0; x < bitmap.pitch; x++)
				{
					byte value = bitmap.buffer[x + y * bitmap.pitch];
					if (value > 0)
						printf("O");
					else
						printf(" ");
				}
				printf("\n");
			}
			printf("\n");
		}
		else
		{
			for (int w = 0; w < 5; w++)
			{
				printf("\n");
			}
		}
	}
}

void FontManager::Init()
{
	int error = FT_Init_FreeType(&s_FTLib);
	ASSERT(error == FT_Err_Ok);
}