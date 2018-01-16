#pragma once
#include "Common.h"
#include <vector>
#include "math/vec4.h"

struct Block
{
public:
	Block(int width, int height, vec4 color)
	: width(width), height(height), m_Color(color)
	{
	}
public:
	int x, y;
	int width, height;
	vec4 m_Color;

	inline const vec4& getColor() const { return m_Color; }

	bool operator < (const Block& block) const
	{
		return (height < block.height);
	}
};

struct PackLevel
{
public:
	PackLevel(int y, int height) 
	 :	y(y), height(height) 
	{
	}
public:
	int y;
	int height;
};

class Packer
{
public:
	Packer(int width, int height);
	void Sort(std::vector<Block>& blocks);
private:
	std::vector<PackLevel> m_Levels;
	int m_MaxWidth;
	int m_MaxHeight;
private:
	void Place(std::vector<Block>& blocks, int index, int currentHeight);
};

