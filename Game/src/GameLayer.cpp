#include "GameLayer.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "graphics/Camera/PerspectiveCamera.h"
#include "debug/DebugGraphics.h"
#include "Application.h"
#include "Resource.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "game/Entity.h"

GameLayer::GameLayer(const String& name)
	: Layer(name)
{
	m_Camera = new OrthographicCamera(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f);
	m_Renderer->SetCamera(m_Camera);

	ASSERT(Resource::LoadShader("Shader", "Shaders/shader.vert", "Shaders/shader.frag"));

	Shader* shader = Resource::GetAs<Shader>("Shader");
	shader->SetTextureIDs("u_Textures");

	m_Level = new Level();
	m_Entity = new Entity();
	Init();

//	ASSERT(Resource::LoadTexture("Jungle", "res/jungle.png"));
//	ASSERT(Resource::LoadTexture("Jungle2", "res/jungle2.png"));
//	ASSERT(Resource::LoadTexture("Jungle3", "res/jungle3.png"));
//	ASSERT(Resource::LoadTexture("Jungle4", "res/jungle4.png"));
}

void GameLayer::Init()
{
	m_Level->OnInit();
	m_Level->Add(m_Entity);
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
//  return;

	m_Renderer->Begin();

	m_Level->OnRender();

	m_Renderer->End();
	m_Renderer->Flush();
}
