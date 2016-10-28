#pragma once

#include <queue>
#include "Renderable2D.h"

struct RenderCommand
{
	Renderable2D* renderable;
};

class Renderer2D
{
private:
	std::queue<RenderCommand> m_Queue;
public:
	void Begin();
	void Submit(Renderable2D* renderable);
	void End();

	void Flush();
};
