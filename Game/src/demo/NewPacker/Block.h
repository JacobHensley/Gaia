#pragma once
#include "graphics/Sprite.h"
#include "Common.h"

class Block
{
public:
	Block(int x, int y, vec4 color);
public:
	int m_X, m_Y;
	int m_Width, m_Height;
	Sprite m_Sprite;
	vec4 m_Color;
};

