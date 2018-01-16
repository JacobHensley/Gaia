#include "Packer.h"
#include <algorithm>

Packer::Packer(int width, int height)
 :	m_MaxWidth(width), m_MaxHeight(height)
{
}

void Packer::Sort(std::vector<Block>& blocks)
{
	std::sort(blocks.begin(), blocks.end());
	bool foundLevel = false;
	int currentHeight = 0;

	for (int i = 0;i < blocks.size();i++) 
	{
		foundLevel = false;
		currentHeight = 0;
		for (int n = 0;n < m_Levels.size();n++)
		{
			if (blocks[i].height <= m_Levels[n].height)
			{
				Place(blocks, i, m_Levels[n].y);
				foundLevel = true;
				currentHeight = 0;
			}
			currentHeight += m_Levels[n].height;
		}
		if (!foundLevel)
		{
			m_Levels.push_back(PackLevel(currentHeight, blocks[i].height));
			Place(blocks, i, currentHeight);
			foundLevel = true;
			currentHeight = 0;
		}
	}
}

void Packer::Place(std::vector<Block>& blocks, int index, int currentHeight)
{
	blocks[index].y = currentHeight;

	int nextX = 0;
	for (int i = 0;i < blocks.size();i++)
	{
		if (blocks[i].x + blocks[i].height > nextX && blocks[i].y == blocks[index].y)
			nextX = blocks[i].x + blocks[i].width;
	}

	blocks[index].x = nextX;
}
