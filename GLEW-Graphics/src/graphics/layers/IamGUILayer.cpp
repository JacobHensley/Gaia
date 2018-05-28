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
bool active = false;
void IamGUILayer::OnRender()
{
	using namespace ImGui;

	ImGui_ImplGlfwGL3_NewFrame();

	ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
	ImGui::Begin("Same title as another window##1");
	if (ImGui::TreeNode("Basic trees"))
	{
		for (int i = 0; i < 5; i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, "Child", i))
			{
				ImGui::Text("Layer");
				ImGui::SameLine();
				if (ImGui::Checkbox("Test", &active)) {};
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}


	if (ImGui::TreeNode("Basic trees##1"))
	{
		for (int i = 0; i < 5; i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, "Child", i))
			{
				ImGui::Text("Layer");
				ImGui::SameLine();
				if (ImGui::Checkbox("Test", &active)) {};
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}
	ImGui::End();


	ImGui::SetNextWindowPos(ImVec2(400,400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Same title as another window##2");
	if (ImGui::TreeNode("Basic trees"))
	{
		for (int i = 0; i < 5; i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, "Child", i))
			{
				ImGui::Text("Layer");
				ImGui::SameLine();
				if (ImGui::Checkbox("Test", &active)) {};
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}
    ImGui::End();


	ShowDemoWindow();

	Render();
	ImGui_ImplGlfwGL3_RenderDrawData(GetDrawData());
}