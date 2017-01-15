#include "GameLayer.h"
#include "../Rectangle.h"
#include "../Camera/OrthographicCamera.h"
#include "../Camera/PerspectiveCamera.h"
#include "../../Application.h"
#include "../../Resource.h"

GameLayer::GameLayer(const String& name) 
	:	Layer(name), m_zoom(40.0f)
{
	m_Camera = new OrthographicCamera(-m_Width / m_zoom, m_Width / m_zoom, -m_Height / m_zoom, m_Height / m_zoom);
	m_Renderer->setCamera(m_Camera);

	//TODO: Return null if fail
	ASSERT(Resource::LoadShader("Shader", "Shaders/shader.vert", "Shaders/shader.frag"));
	ASSERT(Resource::LoadTexture("Jungle", "res/jungle.png"));

	m_Rectangle = new Rectangle(0, 0, 10, 10);
}

void GameLayer::OnUpdate()
{
	m_Camera->OnUpdate();

	const Application& app = Application::GetApplication();
	if (app.IsKeyPressed(GLFW_KEY_EQUAL)) {
		m_zoom -= 1.0f;
	}
	else if (app.IsKeyPressed(GLFW_KEY_MINUS)) {
		m_zoom += 1.0f;
	}

	if (m_zoom < 1.0f) {
		m_zoom = 1.0f;
	}

	m_Camera->SetProjectionMatrix(mat4::Orthographic(-m_Width / m_zoom, m_Width / m_zoom, -m_Height / m_zoom, m_Height / m_zoom, -1.0f, 1.0f));
}

void GameLayer::OnRender()
{
	m_Renderer->Begin();
	m_Renderer->Submit(m_Rectangle);
	m_Renderer->Submit(m_Rectangle, mat4::Translate(vec3(-20.0f, 0.0f, 0.0f)));
	m_Renderer->Submit(m_Rectangle, mat4::Translate(vec3(20.0f, 0.0f, 0.0f)) * mat4::Rotate(45.0f, vec3(0, 0, 1)));
//	for (int i = 0; i < 1;i++) {
//		m_Renderer->Submit(&rectangle);
//	}
	m_Renderer->End();
	m_Renderer->Flush();
}
