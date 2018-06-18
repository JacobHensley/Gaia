#include "Renderer2D.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "FontManager.h"

#define RENDERER_VERTEX_SIZE sizeof(Vertex)

#define SHADER_VERTEX_INDEX 0
#define SHADER_TC_INDEX     1
#define SHADER_TID_INDEX    2

struct Vertex
{
	vec3 position;
	vec2 texCoord;
	float textureID;
	vec4 color;
};

Renderer2D::Renderer2D(int width, int height)
	: m_Width(width), m_Height(height), m_Camera(nullptr), m_Buffer(nullptr), m_IndexCount(0), m_LineIndexCount(0)
{
	Init();
}

void Renderer2D::Init()
{
	const uint MAX_SPRITES = 100000;
	const uint MAX_TEXT_CHARS = 1000;
	const uint MAX_LINE = 2000;

	const uint INDEX_BUFFER_SIZE = MAX_SPRITES * 6;
	const uint LINE_INDEX_BUFFER_SIZE = MAX_LINE * 2;

	uint offset = 0;
	uint* indices = new uint[INDEX_BUFFER_SIZE];
	uint* lineIndices = new uint[MAX_LINE];

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

	BufferLayout layout;
	layout.Push<vec3>("Position");
	layout.Push<vec2>("TexCoord");
	layout.Push<float>("textureID");
	layout.Push<vec4>("Color");

	m_VertexBuffer = new VertexBuffer(MAX_SPRITES * layout.GetStride());
	m_TextVertexBuffer = new VertexBuffer(MAX_TEXT_CHARS * layout.GetStride());

	BufferLayout lineLayout;
	lineLayout.Push<vec3>("Position");
	lineLayout.Push<vec4>("Color");

	m_LineVertexBuffer = new VertexBuffer(MAX_LINE * lineLayout.GetStride());


	m_VertexBuffer->SetLayout(layout);
	m_TextVertexBuffer->SetLayout(layout);
	m_LineVertexBuffer->SetLayout(lineLayout);

	m_IndexBuffer = new IndexBuffer(indices, INDEX_BUFFER_SIZE);
	m_LineIndexBuffer = new IndexBuffer(lineIndices, LINE_INDEX_BUFFER_SIZE);

	delete[] indices;
	delete[] lineIndices;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer2D::Begin()
{
	m_VertexBuffer->Bind();
	m_Buffer = m_VertexBuffer->Map<Vertex>();

	m_TextVertexBuffer->Bind();
	m_TextBuffer = m_TextVertexBuffer->Map<Vertex>();

	m_LineVertexBuffer->Bind();
	m_LineBuffer = m_LineVertexBuffer->Map<Vertex>();
}

void Renderer2D::Submit(Sprite* sprite, float x, float y, float width, float height)
{
	
	float textureID = 0.0f;
	if (sprite->GetTexture())
		textureID = SubmitTexture(sprite->GetTexture());

	m_Buffer->position = vec3(x, y + height);
	m_Buffer->texCoord = vec2(0, 0);
	m_Buffer->color = sprite->m_Color;
	m_Buffer->textureID = textureID;
	m_Buffer++;

	m_Buffer->position = vec3(x, y);
	m_Buffer->texCoord = vec2(0, 1);
	m_Buffer->color = sprite->m_Color;
	m_Buffer->textureID = textureID;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y);
	m_Buffer->texCoord = vec2(1, 1);
	m_Buffer->color = sprite->m_Color;
	m_Buffer->textureID = textureID;
	m_Buffer++;

	m_Buffer->position = vec3(x + width, y + height);
	m_Buffer->texCoord = vec2(1, 0);
	m_Buffer->color = sprite->m_Color;
	m_Buffer->textureID = textureID;
	m_Buffer++;

	m_IndexCount += 6;
}

void Renderer2D::DrawString(const String& text, float x, float y, Font& font, vec4& color)
{
	ftgl::texture_font_t* ftFont = font.GetFont();
	ftgl::texture_atlas_t* ftAtlas = font.GetAtlas();

	Texture* atlasTexture = font.GetAtlasTexture();

	for (int i = 0; i < text.size(); i++)
	{
		char c = text[i];

		ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(ftFont, &c);

		float textureID = SubmitTexture(atlasTexture);

		if (i > 0)
		{
			float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
			x += kerning;
		}

		float x0 = x + glyph->offset_x;
		float y0 = y + (glyph->height - glyph->offset_y);
		float x1 = x + glyph->offset_x + glyph->width;
		float y1 = y - glyph->offset_y;

		m_TextBuffer->position = vec3(x0, y0);
		m_TextBuffer->texCoord = vec2(glyph->s0, glyph->t1);
		m_TextBuffer->color = color;
		m_TextBuffer->textureID = textureID;
		m_TextBuffer++;

		m_TextBuffer->position = vec3(x1, y0);
		m_TextBuffer->texCoord = vec2(glyph->s1, glyph->t1);
		m_TextBuffer->color = color;
		m_TextBuffer->textureID = textureID;
		m_TextBuffer++;

		m_TextBuffer->position = vec3(x1, y1);
		m_TextBuffer->texCoord = vec2(glyph->s1, glyph->t0);
		m_TextBuffer->color = color;
		m_TextBuffer->textureID = textureID;
		m_TextBuffer++;

		m_TextBuffer->position = vec3(x0, y1);
		m_TextBuffer->texCoord = vec2(glyph->s0, glyph->t0);
		m_TextBuffer->color = color;
		m_TextBuffer->textureID = textureID;
		m_TextBuffer++;

		m_IndexCount += 6;

		x += glyph->advance_x;
	}

	font.UpdateAtlasTexture();
}

void Renderer2D::DrawLine(const vec2& point1, const vec2& point2, const vec4& color, float thickness)
{
	m_LineBuffer->position = vec3(point1.x, point1.y);
	m_LineBuffer->color = color;
	m_LineBuffer++;

	m_LineBuffer->position = vec3(point2.x, point2.y);
	m_LineBuffer->color = color;
	m_LineBuffer++;

	m_LineIndexCount += 2;
}

float Renderer2D::SubmitTexture(uint textureID)
{
	float result = 0.0f;

	if (textureID > 0)
	{
		bool found = false;

		for (uint i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == textureID)
			{
				result = (float)(i + 1);
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
			result = (float)(m_TextureSlots.size());
		}
	}
	else {
		std::cout << "Invalid Texture ID" << std::endl;
		ASSERT(false, "Temp");
	}

	return result;
}

float Renderer2D::SubmitTexture(const Texture* texture)
{
	uint textureID = texture->GetTexture();
	return SubmitTexture(textureID);
}

void Renderer2D::End()
{
	m_VertexBuffer->Bind();
	m_VertexBuffer->Unmap();
	m_VertexBuffer->Unbind();

	m_TextVertexBuffer->Bind();
	m_TextVertexBuffer->Unmap();
	m_TextVertexBuffer->Unbind();

	m_LineVertexBuffer->Bind();
	m_LineVertexBuffer->Unmap();
	m_LineVertexBuffer->Unbind();
}

void Renderer2D::Flush()
{
	for (uint i = 0; i < m_TextureSlots.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
	}

	mat4 mvp = m_Camera->GetProjectionMatrix() *  m_Camera->GetViewMatrix() * mat4::Identity();

	if (m_IndexCount > 0)
	{
		//Geometry pass
		{
			Shader* shader = Resource::GetAs<Shader>("Shader");
			shader->Bind();
			shader->SetUniformMat4("u_MVP", mvp);

			m_VertexBuffer->Bind();
			m_IndexBuffer->Bind();

			m_IndexBuffer->Draw(m_IndexCount);
		}

		//Text pass
		{
			Shader* shader = Resource::GetAs<Shader>("TextShader");
			shader->Bind();
			shader->SetUniformMat4("u_MVP", mvp);

			m_TextVertexBuffer->Bind();
			m_IndexBuffer->Bind();

			m_IndexBuffer->Draw(m_IndexCount);
		}

	}

	if (m_LineIndexCount > 0)
	{
		//Line pass

		Shader* shader = Resource::GetAs<Shader>("LineShader");
		shader->Bind();
		shader->SetUniformMat4("u_MVP", mvp);

		m_LineVertexBuffer->Bind();
		m_LineIndexBuffer->Bind();

		m_LineIndexBuffer->DrawLine(m_LineIndexCount);

	}

	m_LineIndexCount = 0;
	m_IndexCount = 0;

#if 0
	while (!m_Queue.empty())
	{
		break;
		RenderCommand command = m_Queue.front();
		m_Queue.pop();

		command.sprite->m_VertexArray->Bind();
		command.sprite->m_IndexBuffer->Bind();
		command.sprite->m_Shader->Bind();
		command.sprite->GetTexture()->Bind();

		command.sprite->m_Shader->SetUniform1i("u_Texture", 0);
		command.sprite->m_Shader->SetUniformMat4("u_ProjMatrix", m_Camera->GetProjectionMatrix());
		command.sprite->m_Shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		command.sprite->m_Shader->SetUniformMat4("u_ModelMatrix", command.transform);

		command.sprite->m_IndexBuffer->Draw();

		command.sprite->GetTexture()->Unbind();
		command.sprite->m_Shader->Unbind();
		command.sprite->m_IndexBuffer->Unbind();
		command.sprite->m_VertexArray->Unbind();
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