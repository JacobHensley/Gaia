#include "Application.h"
#include "debug/DebugLayer.h"
#include <GLFW/glfw3.h>
#include "utils/TimeStep.h"

Application* Application::s_Application = nullptr;

Application::Application(const String& name, int width, int height)
{
	s_Application = this;
	m_Window = new Window(name.c_str(), width, height);
//	PushOverlay(new DebugLayer());
}

Application::~Application()
{
	//TODO: Delete Layers/Overlay
	Shutdown();
	delete m_Window;
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.push_back(layer);
}

void Application::PushOverlay(Layer* layer)
{
	m_OverlayStack.push_back(layer);
}

void Application::OnRender()
{
	for (int i = 0;i < m_LayerStack.size();i++) 
	{
		if (i == activeLayer)
			m_LayerStack[i]->OnRender();
	}

	for (Layer* layer : m_OverlayStack) {
		layer->OnRender();
	}
}

void Application::OnUpdate(TimeStep timeStep)
{
	for (Layer* layer : m_LayerStack) {
		layer->OnUpdate(timeStep);
	}

	for (Layer* layer : m_OverlayStack) {
		layer->OnUpdate(timeStep);
	}
}

void Application::Run()
{

	while (!m_Window->Closed()) 
	{
		m_TimeStep.Update((float)glfwGetTime());
		OnUpdate(m_TimeStep);

		m_Window->Clear();

		OnRender();

		m_Window->Update();
	}

}

void Application::Shutdown()
{
	//Shutdown list
	Sprite::Shutdown();
}
