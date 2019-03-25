#pragma once
#include "utils/Common.h"
#include "graphics/Texture.h"
#include "math/vec2.h"
#include "graphics/Texture.h"

#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"

struct GAIA_API MeshVertex {
	float x;
	float y;
	float z;
	vec3 normal;
	vec2 texcoord;
};

struct GAIA_API MeshTexture {
	String type;
	String path;
	Texture* texture;
};

class GAIA_API Mesh
{
public:
	Mesh(std::vector<MeshVertex>& vertices, std::vector<uint>& indices, std::vector<MeshTexture>& textures);
private:
	void Init();
public:
	std::vector<MeshVertex> m_Vertices;
	std::vector<uint> m_Indices;
	std::vector<MeshTexture>& m_Textures;

	friend class RenderMesh;
};

class GAIA_API RenderMesh
{
public:
	RenderMesh(const Mesh& mesh);

	void Render() const;
private:
	const Mesh* m_Mesh;

	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;
};