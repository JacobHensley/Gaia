#include "Application.h"
#include "debug/DebugLayer.h"
#include <GLFW/glfw3.h>
#include "utils/TimeStep.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

Application* Application::s_Application = nullptr;

Application::Application(const String& name, int width, int height)
{
	s_Application = this;
	m_Window = new Window(name.c_str(), width, height);
	PushOverlay(new DebugLayer());

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(m_Window->GetWindow(), true);
	ImGui::StyleColorsDark();
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

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!m_Window->Closed()) 
	{
		m_TimeStep.Update((float)glfwGetTime());
		OnUpdate(m_TimeStep);

		m_Window->Clear();

		OnRender();

		{
			ImGui_ImplGlfwGL3_NewFrame();

			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);

			ImGui::Checkbox("Demo Window", &show_demo_window);
			ImGui::Checkbox("Another Window", &show_another_window);

			if (ImGui::Button("Button"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		}

		m_Window->Update();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void Application::Shutdown()
{
	//Shutdown list
	Sprite::Shutdown();
}
