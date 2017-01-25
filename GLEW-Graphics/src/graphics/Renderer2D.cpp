#include "Renderer2D.h"

Renderer2D::Renderer2D(int width, int height) 
	:	m_Width(width), m_Height(height), m_Camera(nullptr) {

}

struct Vertex
{
	vec3 position;
	vec2 tc;
};

Vertex* pointer;
uint indexCount = 0;

void Renderer2D::Begin()
{
	uint ib;
	GLCall(glGenBuffers(1, &ib));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));

	uint offset = 0;
	uint* indices = new uint[60 * 6];
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

	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 60 * 6 * sizeof(uint), indices, GL_STATIC_DRAW));
	delete[] indices;

	uint bufferID;
	GLCall(glGenBuffers(1, &bufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 60 * 4 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), 0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(3 * sizeof(float))));

	GLCall(pointer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
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
	pointer->position = vec3(x, y);
	pointer->tc = vec2(0, 1);
	pointer++;

	pointer->position = vec3(x, y + height);
	pointer->tc = vec2(0, 0);
	pointer++;

	pointer->position = vec3(x + width, y + height);
	pointer->tc = vec2(1, 0);
	pointer++;

	pointer->position = vec3(x + width, y);
	pointer->tc = vec2(1, 1);
	pointer++;
	indexCount += 6;
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

	GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));

	Shader* shader = Resource::GetAs<Shader>("Shader");
	shader->bind();
	Resource::GetAs<Texture>("Jungle")->Bind();

	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMat4("u_ProjMatrix", m_Camera->GetProjectionMatrix());
	shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
	shader->SetUniformMat4("u_ModelMatrix", mat4::Identity());

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	while (!m_Queue.empty())
	{
		break;
		RenderCommand command = m_Queue.front();
		m_Queue.pop();

		command.renderable->m_VertexArray->bind();
		command.renderable->m_IndexBuffer->bind();
		command.renderable->m_Shader->bind();
		command.renderable->m_Texture->Bind();

		command.renderable->m_Shader->SetUniform1i("u_Texture", 0);
		command.renderable->m_Shader->SetUniformMat4("u_ProjMatrix", m_Camera->GetProjectionMatrix());
		command.renderable->m_Shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		command.renderable->m_Shader->SetUniformMat4("u_ModelMatrix", command.transform);

		command.renderable->m_IndexBuffer->draw();

		command.renderable->m_Texture->Unbind();
		command.renderable->m_Shader->unbind();
		command.renderable->m_IndexBuffer->unbind();
		command.renderable->m_VertexArray->unbind();
	}
}