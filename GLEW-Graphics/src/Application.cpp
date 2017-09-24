#include "Application.h"
#include "debug/DebugGraphics.h"
#include <GLFW/glfw3.h>
#include <Windows.h>

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

void Application::OnUpdate(float timeStep)
{
	for (Layer* layer : m_LayerStack) {
		layer->OnUpdate(timeStep);
	}

	for (Layer* layer : m_OverlayStack) {
		layer->OnUpdate(timeStep);
	}
}
float lastUpdate = 0.0f;
float updateTime = 0.0f;

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

		OnUpdate(lastUpdate);
		updateTime = (float)glfwGetTime() * 1000;

		m_Window->Clear();
		
		OnRender();
	//	Sleep(50); //For testing timeStep

		m_Window->Update();

		lastUpdate = (float)glfwGetTime() * 1000 - updateTime;
	}
}

void Application::Shutdown()
{
	//Shutdown list
	Sprite::Shutdown();
}
