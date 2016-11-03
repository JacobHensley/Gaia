#include "Application.h"

Application* Application::s_Application = nullptr;

Application::Application(const String& name, int width, int height) {
	s_Application = this;
	m_Window = new Window(name.c_str(), width, height);
}

Application::~Application()
{
	delete m_Window;
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.push_back(layer);
}

void Application::OnRender()
{
	for (Layer* layer : m_LayerStack) {
		layer->OnRender();
	}
}

void Application::Run()
{
	while (!m_Window->closed()) {
//		if (m_Window->GetWidth() != renderer.GetWidth() || m_Window->GetHeight() != renderer.GetHeight())
//			renderer.OnResize(m_Window->GetWidth(), m_Window->GetHeight());

		m_Window->clear();

		OnRender();

		m_Window->update();
	}
}
