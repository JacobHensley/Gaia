#include "Renderable2D.h"

Renderable2D::Renderable2D()
	: m_VertexArray(nullptr), m_IndexBuffer(nullptr), m_Shader(nullptr), m_Texture(nullptr), m_Transform(mat4::Identity())
{
}

Renderable2D::~Renderable2D()
{

}
