#include "GameLayer.h"
#include "../Rectangle.h"
#include "../Camera/OrthographicCamera.h"
#include "../Camera/PerspectiveCamera.h"
#include "../../Application.h"
#include "../../Resource.h"
#include <vector>

#include "debug/DebugGraphics.h"


GameLayer::GameLayer(const String& name)
	: Layer(name), m_Zoom(40.0f)
{
	m_Camera = new OrthographicCamera(-m_Width / m_Zoom, m_Width / m_Zoom, -m_Height / m_Zoom, m_Height / m_Zoom);
	m_Renderer->SetCamera(m_Camera);

	ASSERT(Resource::LoadShader("Shader", "Shaders/shader.vert", "Shaders/shader.frag"));

	ASSERT(Resource::LoadTexture("Jungle", "res/jungle.png"));
	ASSERT(Resource::LoadTexture("Jungle2", "res/jungle2.png"));
	ASSERT(Resource::LoadTexture("Jungle3", "res/jungle3.png"));
	ASSERT(Resource::LoadTexture("Jungle4", "res/jungle4.png"));

	Shader* shader = Resource::GetAs<Shader>("Shader");
	shader->SetTextureIDs("u_Textures");
	  
	texture = Resource::GetAs<Texture>("Jungle");
	m_Rectangle = new Rectangle(0, 0, 10, 10);
}

void GameLayer::OnUpdate()
{
	m_Camera->OnUpdate();

	const Application& app = Application::GetApplication();
	if (app.IsKeyPressed(GLFW_KEY_EQUAL)) {
		m_Zoom -= 1.0f;
	}
	else if (app.IsKeyPressed(GLFW_KEY_MINUS)) {
		m_Zoom += 1.0f;
	}

	if (m_Zoom < 1.0f) {
		m_Zoom = 1.0f;
	}

	m_Camera->SetProjectionMatrix(mat4::Orthographic(-m_Width / m_Zoom, m_Width / m_Zoom, -m_Height / m_Zoom, m_Height / m_Zoom, -1.0f, 1.0f));
}

void GameLayer::OnRender()
{
//	DebugGraphics::FillRectangle(vec2(0, 0), vec2(10, 10));
	//return;

	m_Renderer->Begin();

	m_Renderer->Submit(m_Rectangle, Resource::GetAs<Texture>("Jungle"), -30, 0, 5, 5);
	m_Renderer->Submit(m_Rectangle, Resource::GetAs<Texture>("Jungle2"), -20, 0, 5, 5);
	m_Renderer->Submit(m_Rectangle, Resource::GetAs<Texture>("Jungle3"), -10, 0, 5, 5);
	m_Renderer->Submit(m_Rectangle, Resource::GetAs<Texture>("Jungle4"), 0, 0, 5, 5);

	float xs = 64.0f / 160.0f;
	float ys = 32.0f / 90.0f;
	for (float y = -18.0f; y < 18.0f; y += ys)
	{
		for (float x = -32.0f; x < 32.0f; x += xs)
		{
//			m_Renderer->Submit(m_Rectangle, texture, x, y, xs, ys);
		}
	}

	m_Renderer->End();
	m_Renderer->Flush();
}
