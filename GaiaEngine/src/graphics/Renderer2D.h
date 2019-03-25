#pragma once

#include "Camera/Camera.h"
#include "Sprite.h"
#include "Texture.h"
#include "Font.h"

struct Vertex;
struct LineVertex;

class GAIA_API Renderer2D
{
private:
	int m_Width, m_Height;
	CameraRef m_Camera;

	LineVertex* m_LineBuffer;
	LineVertex* m_LineBufferPtr;

	Vertex* m_TextBuffer;
	Vertex* m_TextBufferPtr;

	Vertex* m_Buffer;
	Vertex* m_BufferPtr;


	VertexBuffer* m_LineVertexBuffer;
	VertexBuffer* m_TextVertexBuffer;
	VertexBuffer* m_VertexBuffer;

	IndexBufferRef m_LineIndexBuffer;
	IndexBufferRef m_IndexBuffer;

	uint m_IndexCount;
	uint m_LineIndexCount;

	std::vector<uint> m_TextureSlots;
public:
	Renderer2D(int width, int height);

	void Begin();

	void Submit(Sprite* sprite, float x, float y, float width, float height);

	void DrawString(const String& text, float x, float y, Font& font, vec4& color);
	void DrawLine(const vec2& point1, const vec2& point2, const vec4& color, float thickness);

	void End();
	void Flush();

	void SetCamera(CameraRef camera);
	void OnResize(int width, int height);

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
private:
	void Init();
	float SubmitTexture(const Texture* texture);
	float SubmitTexture(uint textureID);
};
