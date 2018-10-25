#include "DebugLayer.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "utils/TimeStep.h"

DebugLayer* DebugLayer::s_Instance = nullptr;

DebugLayer::DebugLayer()
	: Layer("DebugLayer")
{
	s_Instance = this;

	const float zoom = 40.0f;
	m_Camera = new OrthographicCamera(-m_Width / zoom, m_Width / zoom, -m_Height / zoom, m_Height / zoom);

	m_Renderer->SetCamera(m_Camera);
}

void DebugLayer::OnUpdate(TimeStep timeStep)
{
}

void DebugLayer::OnRender()
{
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

void DebugLayer::DrawSprite(Sprite* sprite, const mat4& transform)
{
	m_RenderBuffer.push_back(new RenderCommand(sprite, transform));
}