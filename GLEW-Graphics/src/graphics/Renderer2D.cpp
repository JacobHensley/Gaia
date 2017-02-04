#include "Renderer2D.h"

struct Vertex
{
	vec3 position;
	vec2 tc;
};

Renderer2D::Renderer2D(int width, int height) 
	:	m_Width(width), m_Height(height), m_Camera(nullptr), m_Buffer(nullptr), m_IndexCount(0) {
	Init();
}


void Renderer2D::Init()
{

	const uint INDEX_BUFFER_SIZE = 60 * 6;
	uint offset = 0;
	uint* indices = new uint[INDEX_BUFFER_SIZE];
	for (int i = 0; i < 60; i += 6)
	{
		indices[i + 0] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;
		offset += 4;
	}

	m_IndexBuffer = new IndexBuffer(indices, INDEX_BUFFER_SIZE);
	delete[] indices;

	m_VertexBuffer = new Buffer(60 * 4);

	m_VertexBuffer->Bind();

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), 0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(3 * sizeof(float))));
}

void Renderer2D::Begin()
{
	m_VertexBuffer->Bind();
	m_Buffer = m_VertexBuffer->Map<Vertex>();
}

void Renderer2D::Submit(Renderable2D* renderable)
{
	m_Queue.push(RenderCommand { renderable, renderable->m_Transform});
}

void Renderer2D::Submit(Renderable2D* renderable, const mat4& transform)
{
	m_Queue.push(RenderCommand{ renderable, transform });
}

void Renderer2D::Submit(Renderable2D* renderable, float x, float y, float width, float height)
{
	m_Buffer->position = vec3(x, y);
	m_Buffer->tc = vec2(0, 1);
	m_Buffer++;

	m_Buffer->position = vec3(x, y + height);
	m_Buffer->tc = vec2(0, 0);
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y + height);
	m_Buffer->tc = vec2(1, 0);
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y);
	m_Buffer->tc = vec2(1, 1);
	m_Buffer++;
	m_IndexCount += 6;
}

void Renderer2D::End()
{
	m_VertexBuffer->Unmap();
	m_VertexBuffer->Unbind();
}

void Renderer2D::SetCamera(Camera* camera)
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

	Shader* shader = Resource::GetAs<Shader>("Shader");
	shader->Bind();
	Resource::GetAs<Texture>("Jungle")->Bind();

	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMat4("u_ProjMatrix", m_Camera->GetProjectionMatrix());
	shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
	shader->SetUniformMat4("u_ModelMatrix", mat4::Identity());

	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	m_IndexBuffer->Draw(m_IndexCount);

	m_IndexBuffer->Unbind();
	m_VertexBuffer->Unbind();

#if 0
	while (!m_Queue.empty())
	{
		break;
		RenderCommand command = m_Queue.front();
		m_Queue.pop();

		command.renderable->m_VertexArray->Bind();
		command.renderable->m_IndexBuffer->Bind();
		command.renderable->m_Shader->Bind();
		command.renderable->m_Texture->Bind();

		command.renderable->m_Shader->SetUniform1i("u_Texture", 0);
		command.renderable->m_Shader->SetUniformMat4("u_ProjMatrix", m_Camera->GetProjectionMatrix());
		command.renderable->m_Shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		command.renderable->m_Shader->SetUniformMat4("u_ModelMatrix", command.transform);

		command.renderable->m_IndexBuffer->Draw();

		command.renderable->m_Texture->Unbind();
		command.renderable->m_Shader->Unbind();
		command.renderable->m_IndexBuffer->Unbind();
		command.renderable->m_VertexArray->Unbind();
	}
#endif
}