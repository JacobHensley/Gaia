#include "GaPCH.h"
#include "Renderer2D.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "FontManager.h"

struct Vertex
{
	vec3 position;
	vec2 texCoord;
	float textureID;
	vec4 color;
};

struct LineVertex
{
	vec3 position;
	vec4 color;
};

Renderer2D::Renderer2D(int width, int height)
	: m_Width(width), m_Height(height), m_Camera(nullptr), m_Buffer(nullptr), m_IndexCount(0), m_LineIndexCount(0)
{
	Init();
}

void Renderer2D::Init()
{
	// Object count
	const uint MAX_SPRITES = 100000;
	const uint MAX_TEXT_CHARS = 1000;
	const uint MAX_LINES = 1000;

	// Vertex count
	const uint QUAD_VERTEX_BUFFER_COUNT = MAX_SPRITES * 4;
	const uint LINE_VERTEX_BUFFER_COUNT = MAX_LINES * 2;

	// Index count
	const uint QUAD_INDEX_BUFFER_COUNT = MAX_SPRITES * 6;
	const uint LINE_INDEX_BUFFER_COUNT = MAX_LINES * 2;

	std::vector<uint> qaudIndices(QUAD_INDEX_BUFFER_COUNT);
	std::vector<uint> lineIndices(LINE_INDEX_BUFFER_COUNT);

	uint offset = 0;

	for (int i = 0; i < QUAD_INDEX_BUFFER_COUNT; i += 6)
	{
		qaudIndices[i + 0] = offset;
		qaudIndices[i + 1] = offset + 1;
		qaudIndices[i + 2] = offset + 2;

		qaudIndices[i + 3] = offset + 2;
		qaudIndices[i + 4] = offset + 3;
		qaudIndices[i + 5] = offset + 0;
		offset += 4;
	}

	for (int i = 0; i < LINE_INDEX_BUFFER_COUNT; i++)
		lineIndices[i] = i;

	BufferLayout qaudLayout;
	qaudLayout.Push<vec3>("Position");
	qaudLayout.Push<vec2>("TexCoord");
	qaudLayout.Push<float>("textureID");
	qaudLayout.Push<vec4>("Color");

	BufferLayout lineLayout;
	lineLayout.Push<vec3>("Position");
	lineLayout.Push<vec4>("Color");

	m_VertexBuffer = new VertexBuffer(QUAD_VERTEX_BUFFER_COUNT * qaudLayout.GetStride());
	m_TextVertexBuffer = new VertexBuffer(QUAD_VERTEX_BUFFER_COUNT * qaudLayout.GetStride());
	m_LineVertexBuffer = new VertexBuffer(LINE_VERTEX_BUFFER_COUNT * lineLayout.GetStride());

	m_Buffer = new Vertex[QUAD_VERTEX_BUFFER_COUNT];
	m_TextBuffer = new Vertex[QUAD_VERTEX_BUFFER_COUNT];
	m_LineBuffer = new LineVertex[LINE_VERTEX_BUFFER_COUNT];

	m_VertexBuffer->SetLayout(qaudLayout);
	m_TextVertexBuffer->SetLayout(qaudLayout);
	m_LineVertexBuffer->SetLayout(lineLayout);

	m_IndexBuffer = new IndexBuffer(qaudIndices.data(), QUAD_INDEX_BUFFER_COUNT);
	m_LineIndexBuffer = new IndexBuffer(lineIndices.data(), LINE_INDEX_BUFFER_COUNT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer2D::Begin()
{
	m_BufferPtr = m_Buffer;

	m_TextBufferPtr = m_TextBuffer;

	m_LineBufferPtr = m_LineBuffer;
}

void Renderer2D::Submit(Sprite* sprite, float x, float y, float width, float height)
{
	
	float textureID = 0.0f;
	if (sprite->GetTexture())
		textureID = SubmitTexture(sprite->GetTexture());

	m_BufferPtr->position = vec3(x, y + height);
	m_BufferPtr->texCoord = vec2(0, 0);
	m_BufferPtr->color = sprite->m_Color;
	m_BufferPtr->textureID = textureID;
	m_BufferPtr++;

	m_BufferPtr->position = vec3(x, y);
	m_BufferPtr->texCoord = vec2(0, 1);
	m_BufferPtr->color = sprite->m_Color;
	m_BufferPtr->textureID = textureID;
	m_BufferPtr++;

	m_BufferPtr->position = vec3(x + width, y);
	m_BufferPtr->texCoord = vec2(1, 1);
	m_BufferPtr->color = sprite->m_Color;
	m_BufferPtr->textureID = textureID;
	m_BufferPtr++;

	m_BufferPtr->position = vec3(x + width, y + height);
	m_BufferPtr->texCoord = vec2(1, 0);
	m_BufferPtr->color = sprite->m_Color;
	m_BufferPtr->textureID = textureID;
	m_BufferPtr++;

	m_IndexCount += 6;
}

void Renderer2D::DrawString(const String& text, float x, float y, Font& font, vec4& color)
{
	ftgl::texture_font_t* ftFont = font.GetFont();
	ftgl::texture_atlas_t* ftAtlas = font.GetAtlas();

	Texture* atlasTexture = font.GetAtlasTexture();

	for (uint i = 0; i < text.size(); i++)
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

		m_TextBufferPtr->position = vec3(x0, y0);
		m_TextBufferPtr->texCoord = vec2(glyph->s0, glyph->t1);
		m_TextBufferPtr->color = color;
		m_TextBufferPtr->textureID = textureID;
		m_TextBufferPtr++;

		m_TextBufferPtr->position = vec3(x1, y0);
		m_TextBufferPtr->texCoord = vec2(glyph->s1, glyph->t1);
		m_TextBufferPtr->color = color;
		m_TextBufferPtr->textureID = textureID;
		m_TextBufferPtr++;

		m_TextBufferPtr->position = vec3(x1, y1);
		m_TextBufferPtr->texCoord = vec2(glyph->s1, glyph->t0);
		m_TextBufferPtr->color = color;
		m_TextBufferPtr->textureID = textureID;
		m_TextBufferPtr++;

		m_TextBufferPtr->position = vec3(x0, y1);
		m_TextBufferPtr->texCoord = vec2(glyph->s0, glyph->t0);
		m_TextBufferPtr->color = color;
		m_TextBufferPtr->textureID = textureID;
		m_TextBufferPtr++;

		m_IndexCount += 6;

		x += glyph->advance_x;
	}

	font.UpdateAtlasTexture();
}

void Renderer2D::DrawLine(const vec2& point1, const vec2& point2, const vec4& color, float thickness)
{
	m_LineBufferPtr->position = vec3(point1.x, point1.y);
	m_LineBufferPtr->color = color;
	m_LineBufferPtr++;

	m_LineBufferPtr->position = vec3(point2.x, point2.y);
	m_LineBufferPtr->color = color;
	m_LineBufferPtr++;

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
		ASSERT(false);
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
	glBufferSubData(GL_ARRAY_BUFFER, 0, (m_BufferPtr - m_Buffer) * sizeof(Vertex), m_Buffer);
	m_VertexBuffer->Unbind();

	m_TextVertexBuffer->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, (m_TextBufferPtr - m_TextBuffer) * sizeof(Vertex), m_TextBuffer);
	m_TextVertexBuffer->Unbind();

	m_LineVertexBuffer->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, (m_LineBufferPtr - m_LineBuffer) * sizeof(LineVertex), m_LineBuffer);
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