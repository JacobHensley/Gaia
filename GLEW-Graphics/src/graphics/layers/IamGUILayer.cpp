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
	using namespace ImGui;

	Application& app = Application::GetApplication();

	ImGui_ImplGlfwGL3_NewFrame();
	ImGui::Begin("Debug Info");

	ImGui::Text("FPS | %f", app.GetFPS());
	ImGui::Text("MS/F | %f", app.GetMSFrame());

	ImGui::Separator();

	std::vector<Layer*> layers = app.GetLayers();
	if (ImGui::TreeNode("Layers"))
	{
		for (int i = 0; i < layers.size(); i++)
			if (ImGui::TreeNode(layers[i]->GetName().c_str()))
			{
				ImGui::Text("Placeholder");
				ImGui::Selectable("IsActive", &layers[i]->m_IsActive);
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}

	std::vector<Layer*> overlays = app.GetOverlays();
	if (ImGui::TreeNode("Overlays"))
	{
		for (int i = 0; i < overlays.size(); i++)
			if (ImGui::TreeNode(overlays[i]->GetName().c_str()))
			{
				ImGui::Text("Placeholder");
				ImGui::Selectable("IsActive", &overlays[i]->m_IsActive);
				ImGui::TreePop();
			}
		ImGui::TreePop();
	} 

	ImGui::Separator();

	ImGui::End();

	ShowDemoWindow();

	Render();
	ImGui_ImplGlfwGL3_RenderDrawData(GetDrawData());
}
