#include "DebugGraphics.h"
#include "graphics\Camera\OrthographicCamera.h"
#include "graphics\Rectangle.h"

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
	m_Renderer->Begin();

	for (RenderCommand* command : m_RenderBuffer) 
	{
		mat4& transform = command->transform;
		vec3 translation = transform.GetPosition();
		vec3 scale = transform.GetScale();
	//  Commented out as method no longer exists
	//	m_Renderer->Submit(command->renderable, command->texture, translation.x, translation.y, scale.x, scale.y);
		delete command;
	}

	m_Renderer->End();
	m_Renderer->Flush();

	m_RenderBuffer.clear();
}

void DebugGraphics::FillRectangle(const vec2& position, const vec2& size, int color)
{
	ASSERT(s_Instance);

	Rectangle* rectangle = new Rectangle(0.0f, 0.0f, 1.0f, 1.0f);
	mat4 transform = mat4::Translate(vec3(position)) * mat4::Scale(vec3(size));

	//TODO: std::Move
	s_Instance->m_RenderBuffer.push_back(new RenderCommand{ rectangle, nullptr, transform });
}