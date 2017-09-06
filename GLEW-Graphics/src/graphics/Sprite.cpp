#include "Sprite.h"

VertexBuffer* Sprite::m_VertexBuffer = nullptr;
IndexBuffer* Sprite::m_IndexBuffer = nullptr;
Shader* Sprite::m_Shader = nullptr;

Sprite::Sprite()
{
	m_Color = vec4(1, 0, 0, 1);
	Init();
}

Sprite::Sprite(const vec4& color)
 : m_Color(color), m_Texture(nullptr)
{ 
	Init();
}

Sprite::Sprite(const Texture* texture)
	: m_Color(1.0f), m_Texture(texture)
{	
	Init();
}

Sprite::Sprite(const Texture* texture, const vec4& color)
	: m_Texture(texture),  m_Color(color)
{
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

void Sprite::Shutdown()
{
	delete m_VertexBuffer;
	delete m_IndexBuffer;
}
