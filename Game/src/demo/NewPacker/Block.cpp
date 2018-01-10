#include "Block.h"

Block::Block(int x, int y, vec4 color)
	: m_X(x), m_Y(y), m_Color(color) {
	m_Width = 10;
	m_Height = 10;
}
