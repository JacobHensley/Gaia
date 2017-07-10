#include "Sprite.h"

VertexBufferRef Sprite::m_VertexBuffer;
IndexBufferRef Sprite::m_IndexBuffer;
Shader* Sprite::m_Shader;

Sprite::Sprite()
{
	m_Color = vec4(1, 0, 0, 1);
	Init();
}

Sprite::Sprite(vec4 color)
 : m_Color(color) { 
	Init();
}

void Sprite::Init()
{
	if (!m_Shader) 
	{
		float hwidth = 0.5f;
		float hheight = 0.5f;
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f
		};

		uint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VertexBuffer = new VertexBuffer(vertices, 4 * 5, 3);
		m_IndexBuffer = new IndexBuffer(indices, 6);
		m_Shader = Resource::GetAs<Shader>("Shader");
	}
}
