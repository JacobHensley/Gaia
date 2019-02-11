#include "GameLayer.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "graphics/Camera/PerspectiveCamera.h"
#include "Application.h"
#include "utils/Resource.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "game/Entity.h"
#include "game/component/TransformComponent.h"
#include "game/component/SpriteComponent.h"
#include "Components/PlayerComponent.h"
#include "utils/TimeStep.h"
#include "graphics/FontManager.h"
#include "graphics/Material.h"
#include "imgui.h"
#include "graphics/Camera/MayaCamera.h"
#include "ImGuizmo.h"
#include "utils/Log.h"

GameLayer::GameLayer(const String& name)
	: Layer(name)
{
	m_Camera = new MayaCamera(mat4::Perspective(100, 16.0f/9.0f, 10.0f, 10.0f));
	m_Renderer->SetCamera(m_Camera);

	ASSERT(Resource::LoadShader("TextShader", "shaders/Text.shader"));
	ASSERT(Resource::LoadShader("Shader", "shaders/Basic.shader"));
	ASSERT(Resource::LoadShader("LineShader", "shaders/Line.shader"));
	ASSERT(Resource::LoadShader("BunnyShader", "shaders/Bunny.shader"));
	Shader* shader = Resource::GetAs<Shader>("Shader");

	shader->SetTextureIDs("u_Textures");

	ASSERT(Resource::LoadTexture("Jungle", "res/textures/jungle.png"));

	m_BunnyShader = Resource::GetAs<Shader>("BunnyShader");

	OnInit();
}

void GameLayer::OnInit()
{
	m_Level = new Level();
	m_Level->OnInit();

	Log::Init();

	EntityRef textureEntity = m_Level->CreateEntity<Entity>();
	textureEntity->AddComponent(new TransformComponent(mat4::Identity()));
	textureEntity->AddComponent(new SpriteComponent(Sprite(Resource::GetAs<Texture>("Jungle"))));

	EntityRef colorEntity = m_Level->CreateEntity<Entity>();
	colorEntity->AddComponent(new TransformComponent(mat4::Translate(vec3(0.0f, 0.0f, 0.0f))));
	colorEntity->AddComponent(new SpriteComponent(Sprite(vec4(0.8f, 0.8f, 0.2f, 1.0f))));
	colorEntity->AddComponent(new PlayerComponent());

	model = mat4::Translate(vec3(100, 300, 0));

	m_BunnyModel = new Model("res/models/cube.obj");
}

void GameLayer::OnUpdate(TimeStep timeStep)
{
	m_Camera->OnUpdate(timeStep);
	m_Camera->SetProjectionMatrix(mat4::Perspective(65.0f, 1.778f, 0.01f, 1000.0f));
	m_Level->OnUpdate(timeStep);
}

static void ImGuiDrawMat(mat4& matrix)
{

//	ImGui::DragFloat3("Position", &trans.x, 1.0f, -360.0f, 360.0f);
//	matrix.SetPosition(trans);

	ImGui::Begin("Mat");
	for (int y = 0;y < 4;y++)
	{
		for (int x = 0;x < 4;x++)
		{
			ImGui::Text("%.2f", matrix.elements[x + y * 4]);
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}
	ImGui::Separator();


	auto trans = matrix.GetPosition();
	ImGui::Text("T: %.2f, %.2f, %.2f", trans.x, trans.y, trans.z);
	
	auto rotation = matrix.GetRotation();
	ImGui::Text("R: %.2f, %.2f, %.2f", rotation.x, rotation.y, rotation.z);

	auto scale = matrix.GetScale();
	ImGui::Text("S: %.2f, %.2f, %.2f", scale.x, scale.y, scale.z);

	ImGui::DragFloat3("scale", &scale.x, 1.0f, -360.0f, 360.0f);
	matrix.Scale(scale);

	ImGui::End();
}

void GameLayer::OnRender()
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::SCALE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);

	m_Level->OnRender(m_Renderer);

	m_Renderer->Begin();

	m_Renderer->End();
	m_Renderer->Flush();

	m_BunnyShader->Bind();
	m_BunnyShader->SetUniform3f("u_LightPos", m_LightPos);
	m_BunnyShader->SetUniform3f("u_LightColor", m_LightColor);
	m_BunnyShader->SetUniform3f("u_ObjectColor", m_ObjectColor);

//	mat4 model = mat4::Translate(vec3(0, 0, 0));// * mat4::Rotate(m_Angle.x, vec3(1, 0, 0)) * mat4::Rotate(m_Angle.y, vec3(0, 1, 0)) * mat4::Rotate(m_Angle.z, vec3(0, 0, 1)) * mat4::Scale(vec3(m_Scale));
	mat4 mvp = m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix() * model;

	auto view = mat4::Transpose(m_Camera->GetViewMatrix());
	auto proj = mat4::Transpose(m_Camera->GetProjectionMatrix());
	ImGuizmo::SetOrthographic(false);
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	model = mat4::Transpose(model);
	ImGuizmo::Manipulate(view.elements, proj.elements, mCurrentGizmoOperation, mCurrentGizmoMode, model.elements, NULL, NULL);
	model = mat4::Transpose(model);
	ImGuiDrawMat(model);

	m_BunnyShader->SetUniformMat4("u_MVP", mvp);
	m_BunnyShader->SetUniformMat4("u_ModelMatrix", model);
	m_BunnyModel->Render();

	ImGui::DragFloat("Scale", &m_Scale, 0.05f, 0.0f, 50.0f);
	ImGui::DragFloat3("Angle", &m_Angle.x, 1.0f, -360.0f, 360.0f);
	ImGui::DragFloat3("Light Pos", &m_LightPos.x, 0.5f, -10.0f, 10.0f);
	ImGui::ColorPicker3("Light Color", &m_LightColor.x);
	ImGui::ColorPicker3("Object Color", &m_ObjectColor.x);
}
