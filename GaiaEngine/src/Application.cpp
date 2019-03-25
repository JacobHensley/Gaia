#include "GaPCH.h"
#include "Application.h"
#include "graphics/layers/ImGUILayer.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "utils/TimeStep.h"
#include <GLFW/glfw3.h>
#include "ImGuizmo.h"

Application* Application::s_Application = nullptr;

Application::Application(const String& name, int width, int height)
{
	s_Application = this;
	m_Window = new Window(name.c_str(), width, height);
	m_LayerStack = new LayerStack();
	m_LastTime = glfwGetTime();

	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init("#version 410");

	PushOverlay(new ImGUILayer("ImGUILayer"));
}

Application::~Application()
{
	Shutdown();
	delete m_LayerStack;
	delete m_Window;
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack->PushLayer(layer);
}

void Application::PushOverlay(Layer* layer)
{
	m_LayerStack->PushOverlay(layer);
}

void Application::OnRender()
{
	m_LayerStack->OnRender();
}

void Application::OnUpdate(TimeStep timeStep)
{
	m_LayerStack->OnUpdate(timeStep);
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

		ImGui::GetIO().DisplaySize = ImVec2((float)m_Window->GetWidth(), (float)m_Window->GetHeight());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		OnRender();	

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		m_Window->Update();
		
	}

}

void Application::Shutdown()
{
	//Shutdown list
	Sprite::Shutdown();
}
