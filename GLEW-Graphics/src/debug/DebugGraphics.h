#pragma once

#include "graphics/layers/Layer.h"

class DebugGraphics : public Layer 
{
private:
	struct RenderCommand 
	{
		Renderable2D* renderable;
		Texture* texture;
		mat4 transform;

		RenderCommand(Renderable2D* renderable, Texture* texture, const mat4& transform)
			: renderable(renderable), texture(texture), transform(transform) 
		{
		}

		~RenderCommand()
		{
			delete renderable;
			renderable = nullptr;
		}
	};

private:
	static DebugGraphics* s_Instance;
private:
	std::vector<RenderCommand*> m_RenderBuffer;
public:
	DebugGraphics();
	void OnUpdate() override;
	void OnRender() override;
public:
	static void FillRectangle(const vec2& position, const vec2& size, int color = 0xffffff);
private:

};