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
#include "PlayerComponent.h"
#include "TimeStep.h"
#include "graphics/FontManager.h"

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

//	FontManager::Init();

//	FT_Face font = FontManager::LoadFace("calibri", "res/calibri.ttf");

//	FontManager::WriteText("HELLO WORLD", "calibri", 32);

//	Texture* FontTexture = FontManager::GetTexture("calibri", 'A', 32);

//	EntityRef textureEntity = m_Level->CreateEntity<Entity>();
//	textureEntity->AddComponent(new TransformComponent(mat4::Identity()));
//	textureEntity->AddComponent(new SpriteComponent(Sprite(FontTexture)));

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
