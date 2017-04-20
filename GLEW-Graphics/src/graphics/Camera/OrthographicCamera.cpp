#include "Camera.h"
#include "OrthographicCamera.h"
#include "../../Application.h"
#include <GLFW/glfw3.h>

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
	:	Camera(mat4::Orthographic(left, right, top, bottom, -1, 1))	{
}

void OrthographicCamera::OnUpdate()
{
	const Application& app = Application::GetApplication();

	const float speed = 0.5f;
	vec3 pos = m_View.GetPosition();
	if (app.IsKeyPressed(GLFW_KEY_UP)) 
	{
		pos.y -= speed;
	}	
	else if (app.IsKeyPressed(GLFW_KEY_DOWN))  
	{
		pos.y += speed;
	}

	if (app.IsKeyPressed(GLFW_KEY_LEFT)) 
	{
		pos.x += speed;
	}
	else if (app.IsKeyPressed(GLFW_KEY_RIGHT)) 
	{
		pos.x -= speed;
	}
	
	m_View.SetPosition(pos);
}
