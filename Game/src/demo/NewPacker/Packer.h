#pragma once
#include <vector>
#include "Block.h"

class Packer
{
public:
	Packer(int width, int height);
public:
	int m_Width;
	int m_Height;
	std::vector<Block> m_Blocks;
public:
	void Pack(std::vector<Block> blocks);
};

