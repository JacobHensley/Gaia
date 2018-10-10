#pragma once
#include "utils/Common.h"
#include "graphics/Texture.h"
#include "math/vec2.h"
#include "graphics/Texture.h"

struct MeshVertex {
	float x;
	float y;
	float z;
	vec2 texcoord;
};

struct MeshTexture {
	String type;
	String path;
	Texture* texture;
};

class Mesh
{
public:
	Mesh(std::vector<MeshVertex>& vertices, std::vector<uint>& indices, std::vector<MeshTexture>& textures);
private:
	void Init();
public:
	std::vector<MeshVertex> m_Vertices;
	std::vector<uint> m_Indices;
	std::vector<MeshTexture>& m_Textures;
};