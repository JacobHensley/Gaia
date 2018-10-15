#include "Mesh.h"

#include "graphics/BufferLayout.h"

Mesh::Mesh(std::vector<MeshVertex>& vertices, std::vector<uint>& indices, std::vector<MeshTexture>& textures)
	:	m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
{
	Init();
}

void Mesh::Init()
{

}

RenderMesh::RenderMesh(const Mesh& mesh)
	: m_Mesh(&mesh)
{
	// GLCall(glGenVertexArrays(1, &m_VAO));


	m_VertexBuffer = new VertexBuffer((float*)&mesh.m_Vertices[0], mesh.m_Vertices.size() * 5, 5);
	BufferLayout layout;
	layout.Push<vec3>("position");
	layout.Push<vec2>("texCoord");
	m_VertexBuffer->SetLayout(layout);

	m_IndexBuffer = new IndexBuffer(&mesh.m_Indices[0], mesh.m_Indices.size());
}

void RenderMesh::Render() const
{
	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	m_IndexBuffer->Draw();
}
