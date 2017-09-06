#include "DebugGraphics.h"
#include "graphics\Camera\OrthographicCamera.h"

DebugGraphics* DebugGraphics::s_Instance = nullptr;

DebugGraphics::DebugGraphics()
	: Layer("DebugGraphics")
{
	s_Instance = this;

	const float zoom = 40.0f;
	m_Camera = new OrthographicCamera(-m_Width / zoom, m_Width / zoom, -m_Height / zoom, m_Height / zoom);

	m_Renderer->SetCamera(m_Camera);
}

void DebugGraphics::OnUpdate()
{
}

void DebugGraphics::OnRender()
{
	DrawSprite(new Sprite(vec4(0.3f, 0.8f, 0.2f, 1.0f)), mat4::Translate(vec3(-12.0f, 0.0f, 0.0f)));

	m_Renderer->Begin();

	for (RenderCommand* command : m_RenderBuffer)
	{
		mat4& transform = command->transform;
		vec3 translation = transform.GetPosition();
		vec3 scale = transform.GetScale();

		m_Renderer->Submit(command->sprite, translation.x, translation.y, 10, 10);

		delete command;
	}

	m_Renderer->End();
	m_Renderer->Flush();

	m_RenderBuffer.clear();
}

void DebugGraphics::DrawSprite(Sprite* sprite, const mat4& transform)
{
	m_RenderBuffer.push_back(new RenderCommand(sprite, transform));
}