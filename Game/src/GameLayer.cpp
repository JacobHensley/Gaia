#include "GameLayer.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "graphics/Camera/PerspectiveCamera.h"
#include "debug/DebugGraphics.h"
#include "Application.h"
#include "Resource.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "game/Entity.h"
#include "game/component/TransformComponent.h"
#include "game/component/SpriteComponent.h"

GameLayer::GameLayer(const String& name)
	: Layer(name)
{
	m_Camera = new OrthographicCamera(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f);
	m_Renderer->SetCamera(m_Camera);

	ASSERT(Resource::LoadShader("Shader", "shaders/shader.vert", "shaders/shader.frag"));
	Shader* shader = Resource::GetAs<Shader>("Shader");

	shader->SetTextureIDs("u_Textures");

	ASSERT(Resource::LoadTexture("Jungle", "res/jungle.png"));

	Init();
}

void GameLayer::Init()
{
	m_Level = new Level();
	m_Level->OnInit();
	
	EntityRef textureEntity = m_Level->CreateEntity<Entity>();
	textureEntity->AddComponent(new TransformComponent(mat4::Identity()));
	textureEntity->AddComponent(new SpriteComponent(Sprite(Resource::GetAs<Texture>("Jungle"), vec4(0.4f, 0.1f, 0.1f, 1.0f))));

	EntityRef colorEntity = m_Level->CreateEntity<Entity>();
	colorEntity->AddComponent(new TransformComponent(mat4::Translate(vec3(12.0f, 0.0f, 0.0f))));
	colorEntity->AddComponent(new SpriteComponent(Sprite(vec4(0.8f, 0.3f, 0.2f, 1.0f))));
}

void GameLayer::OnUpdate()
{
	m_Camera->OnUpdate();
	m_Camera->SetProjectionMatrix(mat4::Orthographic(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f, -1.0f, 1.0f));

	m_Level->OnUpdate();
}

void GameLayer::OnRender()
{
//	DebugGraphics::FillRectangle(vec2(0, 0), vec2(10, 10));

	m_Level->OnRender(m_Renderer);
}
