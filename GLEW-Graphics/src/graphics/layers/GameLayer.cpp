#include "GameLayer.h"
#include "../Rectangle.h"
#include "../Camera/OrthographicCamera.h"
#include "../Camera/PerspectiveCamera.h"
#include "../../Application.h"
#include "../../Resource.h"
#include <vector>

std::vector<Renderable2D*> textures;

GameLayer::GameLayer(const String& name) 
	:	Layer(name), m_Zoom(40.0f)
{
	m_Camera = new OrthographicCamera(-m_Width / m_Zoom, m_Width / m_Zoom, -m_Height / m_Zoom, m_Height / m_Zoom);
	m_Renderer->SetCamera(m_Camera);

	//TODO: Return null if fail
	ASSERT(Resource::LoadShader("Shader", "Shaders/shader.vert", "Shaders/shader.frag"));
	ASSERT(Resource::LoadTexture("Jungle", "res/jungle.png"));

	for (int i = 0; i < 1000;i++) {
		textures.push_back(new Rectangle(0, 0, 10, 10));
	}

//	m_Rectangle = new Rectangle(0, 0, 10, 10);
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
	m_Renderer->Begin();

//	m_Renderer->Submit(m_Rectangle, 0 - 5, 0 - 5, 10, 10);
//	m_Renderer->Submit(m_Rectangle, 10, 10, 10, 10);
	
	for (int i = 0; i < textures.size();i++) {
	//	m_Renderer->Submit(textures[i], 0 - 5, 0 - 5, 10, 10);
	}

	m_Renderer->End();
	m_Renderer->Flush();
}
