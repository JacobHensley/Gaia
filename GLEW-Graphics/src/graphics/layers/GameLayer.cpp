#include "GameLayer.h"
#include "../Rectangle.h"

GameLayer::GameLayer(const String& name) 
	:	Layer(name)
{

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
