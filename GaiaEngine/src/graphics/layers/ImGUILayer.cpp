#include "ImGUILayer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "utils/Resource.h"
#include "graphics/shaders/Shader.h"

ImGUILayer::ImGUILayer(const String& name)
	: Layer(name)
{
	OnInit();
}

ImGUILayer::~ImGUILayer()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void ImGUILayer::OnInit()
{
	Application& app = Application::GetApplication();

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(app.GetWindow()->GetWindow(), true);
	ImGui::StyleColorsDark();
}

void ImGUILayer::OnUpdate(TimeStep timeStep)
{
}

void ImGUILayer::OnRender()
{
	Application& app = Application::GetApplication();
	LayerStack* layerStack = app.GetLayerStack();

	ShowLayerMenu(app, layerStack);

	ShowUniformMenu(app, layerStack);

	ImGui::ShowDemoWindow();
}

void ImGUILayer::ShowLayerMenu(Application& app, LayerStack* layerStack)
{
	ImGui::Begin("Layer Info");

	ImGui::Text("FPS | %f", app.GetFPS());
	ImGui::Text("MS/F | %f", app.GetMSFrame());

	ImGui::Separator();

	std::vector<Layer*> layers = layerStack->GetLayers();
	if (ImGui::TreeNode("Layers"))
	{
		for (uint i = 0; i < layers.size(); i++)
			if (ImGui::TreeNode(layers[i]->GetName().c_str()))
			{
				ImGui::Text("Placeholder");
				ImGui::Selectable("IsActive", &layers[i]->m_IsActive);
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}

	std::vector<Layer*> overlays = layerStack->GetOverlays();
	if (ImGui::TreeNode("Overlays"))
	{
		for (uint i = 0; i < overlays.size(); i++)
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
}

void ImGUILayer::ShowUniformMenu(Application& app, LayerStack* layerStack)
{
	ImGui::Begin("Uniform Info");

	for each (auto resource in Resource::GetResourceMap())
	{
		if (resource.second.type == Resource::ResourceType::SHADER)
		{
			Shader* shader = static_cast<Shader*>(resource.second.pointer);
			const std::vector<ShaderUniform*>& uniforms = shader->GetUniforms();

			if (ImGui::TreeNode(resource.first.c_str()))
			{
				for (uint i = 0; i < uniforms.size(); i++)

					if (ImGui::TreeNode(uniforms[i]->GetName().c_str()))
					{
						ImGui::Text("Type:   | %s", uniforms[i]->StringFromType(uniforms[i]->GetType()).c_str());
						ImGui::Text("Count:  | %i", uniforms[i]->GetCount());
						ImGui::Text("Size:   | %i", uniforms[i]->GetSize());
						ImGui::Text("Offset: | %i", uniforms[i]->GetOffset());
						ImGui::TreePop();
					}
				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
}
