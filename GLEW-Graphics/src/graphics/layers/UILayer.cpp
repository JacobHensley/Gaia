#include "UILayer.h"
#include "graphics/Camera/OrthographicCamera.h"

UILayer::UILayer(const String& name)
	: Layer(name)
{
	m_Camera = new OrthographicCamera(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f);
	m_Renderer->SetCamera(m_Camera);
}

void UILayer::OnUpdate(TimeStep timeStep)
{
	m_Camera->OnUpdate(timeStep);
	m_Camera->SetProjectionMatrix(mat4::Orthographic(-m_Width, m_Width, -m_Height, m_Height, -1.0f, 1.0f));
}

void UILayer::OnRender()
{
}
