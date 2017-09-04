#include "Rectangle.h"
#include "../Resource.h"

Rectangle::Rectangle(float x, float y, float width, float height)
	: Renderable2D()
{
	float hwidth = width * 0.5f;
	float hheight = height * 0.5f;
	float vertices[] = {
		x - hwidth, y - hheight, 0.0f, 0.0f, 1.0f,
		x - hwidth, y + hheight, 0.0f, 0.0f, 0.0f,
		x + hwidth, y + hheight, 0.0f, 1.0f, 0.0f,
		x + hwidth, y - hheight, 0.0f, 1.0f, 1.0f
	};

	uint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VertexBuffer = new VertexBuffer(vertices, 4 * 5, 3);
	m_IndexBuffer = new IndexBuffer(indices, 6);

//  TODO: Fix ASSERT
//	ASSERT(m_Shader = Resource::GetAs<Shader>("Shader"));
//	ASSERT(m_Texture = Resource::GetAs<Texture>("Jungle"));
}

Rectangle::~Rectangle()
{

}