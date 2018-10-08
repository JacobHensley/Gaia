#include "Mesh.h"

Mesh::Mesh(std::vector<MeshVertex>& vertices, std::vector<uint>& indices, std::vector<MeshTexture>& textures)
	:	m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
{
	Init();
}

void Mesh::Init()
{

}