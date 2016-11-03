#include "Renderer2D.h"

Renderer2D::Renderer2D(int width, int height) 
	:	m_Width(width), m_Height(height) {

}

void Renderer2D::Begin()
{

}

void Renderer2D::Submit(Renderable2D* renderable)
{
	m_Queue.push(RenderCommand { renderable });
}

void Renderer2D::End()
{

}

void Renderer2D::OnResize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

void Renderer2D::Flush()
{
	while (!m_Queue.empty())
	{
		RenderCommand command = m_Queue.back();
		m_Queue.pop();

		command.renderable->m_VertexArray->bind();
		command.renderable->m_IndexBuffer->bind();
		command.renderable->m_Shader->bind();

	//	mat4 prespective = mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
		mat4 proj = mat4::Orthographic(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f, -1.0f, 1.0f);
		command.renderable->m_Shader->SetUniform1i("u_Texture", 0);
		command.renderable->m_Shader->SetUniformMat4("u_ProjMatrix", proj);
		command.renderable->m_Shader->SetUniformMat4("u_ModelMatrix", command.renderable->m_Transform);

		command.renderable->m_IndexBuffer->draw();
	}
}
