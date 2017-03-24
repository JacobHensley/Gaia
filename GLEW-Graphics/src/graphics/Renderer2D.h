#pragma once

#include <queue>
#include "Renderable2D.h"
#include "Camera\Camera.h"

struct Vertex;

struct RenderCommand
{
	Renderable2D* renderable;
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

	void Submit(Renderable2D* renderable, const mat4& transform);
	void Submit(Renderable2D* renderable);
	void Submit(Renderable2D* renderable, Texture* texture, float x, float y, float width, float height);

	void Submit(const Renderable2DRef& renderable, Texture* texture, float x, float y, float width, float height);

	void End();
	void Flush();

	void SetCamera(CameraRef camera);
	void OnResize(int width, int height);

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
private:
	void Init();
};
