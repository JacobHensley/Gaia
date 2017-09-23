#include "Layer.h"
#include "../../Application.h"

Layer::Layer(const String& name)
	:	m_Name(name), m_Camera(nullptr)	
{
	OnInit();
}

void Layer::OnInit() 
{
	Application& app = Application::GetApplication();
	m_Renderer = new Renderer2D(app.GetWidth(), app.GetHeight());
	
	m_Width = app.GetWidth();
	m_Height = app.GetHeight();
}

void Layer::OnUpdate(float timeStep)
{
}

void Layer::OnRender()
{
}
