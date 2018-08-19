#include "Application.h"
#include "debug/DebugLayer.h"
#include "graphics/layers/IamGUILayer.h"
#include <GLFW/glfw3.h>
#include "utils/TimeStep.h"

Application* Application::s_Application = nullptr;

Application::Application(const String& name, int width, int height)
{
	s_Application = this;
	m_Window = new Window(name.c_str(), width, height);
	m_LastTime = glfwGetTime();

	PushOverlay(new IamGUILayer("DebugOverlay"));
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
		if (m_LayerStack[i]->m_IsActive)
			m_LayerStack[i]->OnRender();
	}

	for (Layer* layer : m_OverlayStack) {
		if (layer->m_IsActive)
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

		double currentTime = glfwGetTime();
		m_NbFrames++;
		if (currentTime - m_LastTime >= 1.0)
		{
			m_MSFrame = 1000.0 / double(m_NbFrames);
			m_FPS = double(m_NbFrames);

			m_NbFrames = 0;
			m_LastTime += 1.0;
		}

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
