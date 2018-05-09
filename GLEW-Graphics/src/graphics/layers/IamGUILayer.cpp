#include "IamGUILayer.h"
#include "Application.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

IamGUILayer::IamGUILayer(const String& name)
	: Layer(name)
{
	OnInit();
}

IamGUILayer::~IamGUILayer()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void IamGUILayer::OnInit()
{
	Application& app = Application::GetApplication();

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(app.GetWindow()->GetWindow(), true);
	ImGui::StyleColorsDark();
}

void IamGUILayer::OnUpdate(TimeStep timeStep)
{
}

void IamGUILayer::OnRender()
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