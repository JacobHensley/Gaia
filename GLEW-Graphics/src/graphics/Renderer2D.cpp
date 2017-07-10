#include "Renderer2D.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#define RENDERER_VERTEX_SIZE sizeof(Vertex)

#define SHADER_VERTEX_INDEX 0
#define SHADER_TC_INDEX     1
#define SHADER_TID_INDEX    2

struct Vertex
{
	vec3 position;
	vec2 tc;
	float tid;
	vec4 color;
};

Renderer2D::Renderer2D(int width, int height)
	: m_Width(width), m_Height(height), m_Camera(nullptr), m_Buffer(nullptr), m_IndexCount(0)
{
	Init();
}

void Renderer2D::Init()
{
	const uint MAX_SPRITES = 100000;

	const uint INDEX_BUFFER_SIZE = MAX_SPRITES * 6;
	uint offset = 0;
	uint* indices = new uint[INDEX_BUFFER_SIZE];

	for (int i = 0; i < MAX_SPRITES; i += 6)
	{
		indices[i + 0] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;
		offset += 4;
	}

	m_VertexBuffer = new VertexBuffer(MAX_SPRITES * sizeof(float) * 5);

	BufferLayout layout;
	layout.Push<vec3>("Position");
	layout.Push<vec2>("TexCoord");
	layout.Push<float>("TexID");
	layout.Push<vec4>("Color");

	m_VertexBuffer->SetLayout(layout);

	m_IndexBuffer = new IndexBuffer(indices, INDEX_BUFFER_SIZE);
	delete[] indices;
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

void Renderer2D::Submit(Renderable2D* renderable, Texture* texture, float x, float y, float width, float height)
{
	float textureSlot = 0.0f;

	if (texture) 
	{
		uint textureID = texture->GetTexture();

		if (textureID > 0)
		{
			bool found = false;

			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == textureID)
				{
					textureSlot = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found)
			{
				if (m_TextureSlots.size() > 32)
				{
					End();
					Flush();
					Begin();
				}
				m_TextureSlots.push_back(textureID);
				textureSlot = (float)(m_TextureSlots.size() - 1);
			}
		}
		else {
			std::cout << "Invalid Texture ID" << std::endl;
			ASSERT(false);
		}
	}
	m_Buffer->position = vec3(x, y);
	m_Buffer->tc = vec2(0, 1);
	m_Buffer->tid = textureSlot;
	m_Buffer++;

	m_Buffer->position = vec3(x, y + height);
	m_Buffer->tc = vec2(0, 0);
	m_Buffer->tid = textureSlot;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y + height);
	m_Buffer->tc = vec2(1, 0);
	m_Buffer->tid = textureSlot;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y);
	m_Buffer->tc = vec2(1, 1);
	m_Buffer->tid = textureSlot;
	m_Buffer++;
	m_IndexCount += 6;
}

void Renderer2D::Submit(Sprite* sprite, float x, float y, float width, float height)
{
	m_Buffer->position = vec3(x, y);
	m_Buffer->tc = vec2(0, 1);
	m_Buffer->color = sprite->m_Color;
	m_Buffer++;

	m_Buffer->position = vec3(x, y + height);
	m_Buffer->tc = vec2(0, 0);
	m_Buffer->color = sprite->m_Color;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y + height);
	m_Buffer->tc = vec2(1, 0);
	m_Buffer->color = sprite->m_Color;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y);
	m_Buffer->tc = vec2(1, 1);
	m_Buffer->color = sprite->m_Color;
	m_Buffer++;
	m_IndexCount += 6;
}

void Renderer2D::Submit(const Renderable2DRef& renderable, Texture* texture, float x, float y, float width, float height)
{
	float textureSlot = 0.0f;

	if (texture) 
	{
		uint textureID = texture->GetTexture();

		if (textureID > 0)
		{
			bool found = false;

			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == textureID)
				{
					textureSlot = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found)
			{
				if (m_TextureSlots.size() > 32)
				{
					End();
					Flush();
					Begin();
				}
				m_TextureSlots.push_back(textureID);
				textureSlot = (float)(m_TextureSlots.size() - 1);
			}
		}
		else {
			std::cout << "Invalid Texture ID" << std::endl;
			ASSERT(false);
		}
	}
	m_Buffer->position = vec3(x, y);
	m_Buffer->tc = vec2(0, 1);
	m_Buffer->tid = textureSlot;
	m_Buffer++;

	m_Buffer->position = vec3(x, y + height);
	m_Buffer->tc = vec2(0, 0);
	m_Buffer->tid = textureSlot;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y + height);
	m_Buffer->tc = vec2(1, 0);
	m_Buffer->tid = textureSlot;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y);
	m_Buffer->tc = vec2(1, 1);
	m_Buffer->tid = textureSlot;
	m_Buffer++;
	m_IndexCount += 6;
}

void Renderer2D::End()
{
	m_VertexBuffer->Unmap();
	m_VertexBuffer->Unbind();
}

void Renderer2D::Flush()
{
//TODO: Fix ASSERT
//	ASSERT(m_Camera);

	for (uint i = 0; i < m_TextureSlots.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
	}

	Shader* shader = Resource::GetAs<Shader>("Shader");
	shader->Bind();

	shader->SetUniformMat4("u_ProjMatrix", m_Camera->GetProjectionMatrix());
	shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
	shader->SetUniformMat4("u_ModelMatrix", mat4::Identity());

	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	m_IndexBuffer->Draw(m_IndexCount);
	
	m_IndexBuffer->Unbind();
	m_VertexBuffer->Unbind();

	m_IndexCount = 0;

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

void Renderer2D::SetCamera(CameraRef camera)
{
	m_Camera = camera;
}

void Renderer2D::OnResize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}