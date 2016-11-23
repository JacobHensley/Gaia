#include "Renderer2D.h"

Renderer2D::Renderer2D(int width, int height) 
	:	m_Width(width), m_Height(height), m_Camera(nullptr) {

}

void Renderer2D::Begin()
{

}

void Renderer2D::Submit(Renderable2D* renderable)
{
	m_Queue.push(RenderCommand { renderable, renderable->m_Transform});
}

void Renderer2D::Submit(Renderable2D * renderable, const mat4 & transform)
{
	m_Queue.push(RenderCommand{ renderable, transform });
}

void Renderer2D::End()
{

}

void Renderer2D::setCamera(Camera* camera)
{
	m_Camera = camera;
}

void Renderer2D::OnResize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

void Renderer2D::Flush()
{
	ASSERT(m_Camera);

	while (!m_Queue.empty())
	{
		RenderCommand command = m_Queue.front();
		m_Queue.pop();

		command.renderable->m_VertexArray->bind();
		command.renderable->m_IndexBuffer->bind();
		command.renderable->m_Shader->bind();

		command.renderable->m_Shader->SetUniform1i("u_Texture", 0);
		command.renderable->m_Shader->SetUniformMat4("u_ProjMatrix", m_Camera->GetProjectionMatrix());
		command.renderable->m_Shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		command.renderable->m_Shader->SetUniformMat4("u_ModelMatrix", command.transform);

		command.renderable->m_IndexBuffer->draw();
	}
}
