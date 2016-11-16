#pragma once

#include <queue>
#include "Renderable2D.h"
#include "Camera\Camera.h"
struct RenderCommand
{
	Renderable2D* renderable;
};

class Renderer2D
{
private:
	std::queue<RenderCommand> m_Queue;
	int m_Width, m_Height;
	Camera* m_Camera;
public:
	Renderer2D(int width, int height);
	void Begin();
	void Submit(Renderable2D* renderable);
	void End();

	void setCamera(Camera* camera);

	void OnResize(int width, int height);

	void Flush();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};
