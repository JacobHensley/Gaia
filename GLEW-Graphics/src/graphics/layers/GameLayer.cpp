#include "GameLayer.h"
#include "../Rectangle.h"
#include "../Camera/OrthographicCamera.h"
#include "../Camera/PerspectiveCamera.h"

GameLayer::GameLayer(const String& name) 
	:	Layer(name)
{
//	m_Renderer->setCamera(new Camera(mat4::Orthographic(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f, -1.0f, 1.0f)));
	m_Renderer->setCamera(new OrthographicCamera(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f));
}

void GameLayer::OnRender()
{
	Rectangle rectangle(0, 0, 10, 10);
	m_Renderer->Begin();
	m_Renderer->Submit(&rectangle);
	m_Renderer->End();
	m_Renderer->Flush();

	rectangle.SetTransform(mat4::Translate(vec3(0.0f, 0.0f, 0.0f)));
}
