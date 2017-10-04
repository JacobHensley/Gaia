#pragma once

#include "graphics/layers/Layer.h"
#include "graphics/Sprite.h"

class DebugGraphics : public Layer 
{
private:
	struct RenderCommand 
	{
		Sprite* sprite;
		mat4 transform;

		RenderCommand(Sprite* sprite, const mat4& transform)
			: sprite(sprite), transform(transform)
		{
		}

		~RenderCommand()
		{
			delete sprite;
			sprite = nullptr;
		}
	};

private:
	static DebugGraphics* s_Instance;
private:
	std::vector<RenderCommand*> m_RenderBuffer;
public:
	DebugGraphics();

	void DrawSprite(Sprite* sprite, const mat4& transform);

	void OnUpdate(TimeStep timeStep) override;
	void OnRender() override;
};