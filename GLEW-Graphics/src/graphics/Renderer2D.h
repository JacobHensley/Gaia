#pragma once

#include <queue>
#include "Camera\Camera.h"
#include "Sprite.h"
#include "Texture.h"
#include "Font.h"

struct Vertex;

struct RenderCommand
{
	Sprite* sprite;
	mat4 transform;
};

class Renderer2D
{
private:
	std::queue<RenderCommand> m_Queue;
	int m_Width, m_Height;
	CameraRef m_Camera;
	Vertex* m_Buffer;
	VertexBuffer* m_VertexBuffer;
	IndexBufferRef m_IndexBuffer;
	uint m_IndexCount;

	std::vector<uint> m_TextureSlots;
public:
	Renderer2D(int width, int height);

	void Begin();

	void Submit(Sprite* sprite, float x, float y, float width, float height);

	void DrawTriangle(const vec4& color, float x, float y, float width, float height);

	void DrawString(const String& text, float x, float y, Font& font, vec4& color);

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
