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

	ImGui_ImplGlfwGL3_NewFrame();

	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (MenuItem("Close", "Ctrl+W")) { /* Do stuff */ }
			ImGui::EndMenu();
		}
		EndMainMenuBar();
	}

	if (ImGui::TreeNode("Basic trees"))
	{
		for (int i = 0; i < 5; i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, "Child", i))
			{
				ImGui::Text("blah blah");
		//		ImGui::SameLine();
				if (ImGui::SmallButton("button")) {};
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}

	static float f = 0.0f;
	static int counter = 0;
	Text("Hello, world!");
	SliderFloat("float", &f, 0.0f, 1.0f);
	ColorEdit3("clear color", (float*)&clear_color);
	Checkbox("Demo Window", &show_demo_window);
	Checkbox("Another Window", &show_another_window);


	Button("Click");     // Label = "Click",  ID = top of id stack + hash of "Click"
	if (TreeNode("node"))
	{
		Button("Click");   // Label = "Click",  ID = top of id stack + hash of "node" + hash of "Click"
		TreePop();
	}

	ShowDemoWindow();

	if (Button("Button"))
		counter++;
	SameLine();
	Text("counter = %d", counter);

	Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / GetIO().Framerate, GetIO().Framerate);

	Render();
	ImGui_ImplGlfwGL3_RenderDrawData(GetDrawData());
}