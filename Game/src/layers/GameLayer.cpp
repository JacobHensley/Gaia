#include "GameLayer.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "graphics/Camera/PerspectiveCamera.h"
#include "debug/DebugLayer.h"
#include "Application.h"
#include "utils/Resource.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "game/Entity.h"
#include "game/component/TransformComponent.h"
#include "game/component/SpriteComponent.h"
#include "PlayerComponent.h"
#include "utils/TimeStep.h"
#include "graphics/FontManager.h"
#include "graphics/Material.h"

GameLayer::GameLayer(const String& name)
	: Layer(name)
{
	m_Camera = new OrthographicCamera(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f);
	m_Renderer->SetCamera(m_Camera);

	ASSERT(Resource::LoadShader("TextShader", "shaders/Text.shader"), "Could not load TextShader into Resource");
	ASSERT(Resource::LoadShader("Shader", "shaders/Basic.shader"), "Could not load Shader into Resource");
	ASSERT(Resource::LoadShader("LineShader", "shaders/Line.shader"), "Could not load LineShader into Resource");
	Shader* shader = Resource::GetAs<Shader>("Shader");

	shader->SetTextureIDs("u_Textures");

//	shader->PrintUniforms();
//	Material material = Material(shader);
//	material.SetValue("u_TestColor", 1);

	ASSERT(Resource::LoadTexture("Jungle", "res/textures/jungle.png"), "Could not load Jungle texture into Resource");

	OnInit();
}

void GameLayer::OnInit()
{
	m_Level = new Level();
	m_Level->OnInit();

	EntityRef textureEntity = m_Level->CreateEntity<Entity>();
	textureEntity->AddComponent(new TransformComponent(mat4::Identity()));
	textureEntity->AddComponent(new SpriteComponent(Sprite(Resource::GetAs<Texture>("Jungle"))));

	EntityRef colorEntity = m_Level->CreateEntity<Entity>();
	colorEntity->AddComponent(new TransformComponent(mat4::Translate(vec3(0.0f, 0.0f, 0.0f))));
	colorEntity->AddComponent(new SpriteComponent(Sprite(vec4(0.8f, 0.8f, 0.2f, 1.0f))));
	colorEntity->AddComponent(new PlayerComponent());
}

void GameLayer::OnUpdate(TimeStep timeStep)
{
	m_Camera->OnUpdate(timeStep);
	m_Camera->SetProjectionMatrix(mat4::Orthographic(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f, -1.0f, 1.0f));

	m_Level->OnUpdate(timeStep);
}

void GameLayer::OnRender()
{
	m_Level->OnRender(m_Renderer);

	m_Renderer->Begin();

	m_Renderer->End();
	m_Renderer->Flush();
}
