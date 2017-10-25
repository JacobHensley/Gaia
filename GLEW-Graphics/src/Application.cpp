#include "Application.h"
#include "debug/DebugGraphics.h"
#include <GLFW/glfw3.h>
#include "TimeStep.h"

Application* Application::s_Application = nullptr;

Application::Application(const String& name, int width, int height)
{
	s_Application = this;
	m_Window = new Window(name.c_str(), width, height);
	PushOverlay(new DebugGraphics());
	lastTime = glfwGetTime();
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
	for (Layer* layer : m_LayerStack) {
		layer->OnRender();
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
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) 
		{
	//		printf("ms/frame: %f", 1000.0 / double(nbFrames));
	//		printf(" | FPS: %f\n", double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
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
