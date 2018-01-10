#include "DemoLayer.h"
#include "graphics/Shader.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "TimeStep.h"
#include "game/component/TransformComponent.h"
#include "game/component/SpriteComponent.h"

DemoLayer::DemoLayer(const String& name)
	:	Layer(name)	
{
	m_Camera = new OrthographicCamera(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f);
	m_Renderer->SetCamera(m_Camera);

	ASSERT(Resource::LoadShader("Shader", "shaders/shader.vert", "shaders/shader.frag"));
	Shader* shader = Resource::GetAs<Shader>("Shader");

	shader->SetTextureIDs("u_Textures");

	ASSERT(Resource::LoadTexture("Jungle", "res/jungle.png"));

	Init();
}

void DemoLayer::Init()
{
	m_Level = new Level();
	m_Level->OnInit();

	EntityRef colorEntity = m_Level->CreateEntity<Entity>();
	colorEntity->AddComponent(new TransformComponent(mat4::Translate(vec3(0.0f, 0.0f, 0.0f))));
	colorEntity->AddComponent(new SpriteComponent(Sprite(vec4(0.8f, 0.8f, 0.2f, 1.0f))));

}

void DemoLayer::OnUpdate(TimeStep timeStep)
{
	m_Camera->OnUpdate(timeStep);
	m_Camera->SetProjectionMatrix(mat4::Orthographic(-m_Width / 40.0f, m_Width / 40.0f, -m_Height / 40.0f, m_Height / 40.0f, -1.0f, 1.0f));

	m_Level->OnUpdate(timeStep);
}

void DemoLayer::OnRender()
{
	m_Level->OnRender(m_Renderer);
}