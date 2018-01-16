#include "DemoLayer.h"
#include "graphics/Shader.h"
#include "graphics/Camera/OrthographicCamera.h"
#include "TimeStep.h"
#include "game/component/TransformComponent.h"
#include "game/component/SpriteComponent.h"
#include "Packer/Packer.h"

DemoLayer::DemoLayer(const String& name)
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

void DemoLayer::Init()
{
	m_Level = new Level();
	m_Level->OnInit();

	Packer packer = Packer(40, 40);

	std::vector<Block> blocks;
	blocks.push_back(Block(1, 1, vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	blocks.push_back(Block(1, 1, vec4(0.9f, 0.9f, 0.9f, 1.0f)));
	blocks.push_back(Block(2, 1, vec4(0.8f, 0.8f, 0.8f, 1.0f)));
	blocks.push_back(Block(1, 1, vec4(0.7f, 0.7f, 0.7f, 1.0f)));
	blocks.push_back(Block(2, 1, vec4(0.6f, 0.6f, 0.6f, 1.0f)));
	blocks.push_back(Block(2, 2, vec4(0.5f, 0.5f, 0.5f, 1.0f)));
	blocks.push_back(Block(1, 3, vec4(0.4f, 0.4f, 0.4f, 1.0f)));
	blocks.push_back(Block(6, 2, vec4(0.3f, 0.3f, 0.3f, 1.0f)));
	packer.Sort(blocks);

	for (int i = 0; i < blocks.size(); i++)
	{
		Block block = blocks[i];
		EntityRef colorEntity = m_Level->CreateEntity<Entity>();
		colorEntity->AddComponent(new TransformComponent(mat4::Translate(vec3(block.x, block.y, 0.0f))));
		colorEntity->AddComponent(new SpriteComponent(Sprite(block.getColor(), block.width, block.height)));
	}

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