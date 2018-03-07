#include "UILayer.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "graphics/FontManager.h"

static Font* s_Font;

UILayer::UILayer(const String& name)
	: Layer(name)
{
	m_Camera = new OrthographicCamera(0, m_Width, 0, m_Height);
	m_Renderer->SetCamera(m_Camera);

	s_Font = new Font("calibri", "res/calibri.ttf", 64);
	FontManager::LoadFont(s_Font);
}

void UILayer::OnUpdate(TimeStep timeStep)
{
	m_Camera->OnUpdate(timeStep);
	m_Camera->SetProjectionMatrix(mat4::Orthographic(0, m_Width, m_Height, 0, -1.0f, 1.0f));
}

void UILayer::OnRender()
{
	m_Renderer->Begin();

	m_Renderer->DrawString("Hello!y", 100.0f, 200.0f, *FontManager::GetFont("calibri", 64), vec4(1.0f));

	m_Renderer->End();
	m_Renderer->Flush();
}
