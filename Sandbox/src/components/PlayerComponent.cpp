#include "PlayerComponent.h"
#include "game/Level.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "math.h"

void PlayerComponent::OnCreate()
{
	m_Transform = GetComponent<TransformComponent>();
	m_Sprite = GetComponent<SpriteComponent>();
}

void PlayerComponent::OnUpdate(TimeStep timeStep)
{
	Application& app = Application::GetApplication();
	float speed = (float)(0.1 * timeStep.GetMills());
	vec3 pos = m_Transform->m_Transform.GetPosition();

	if (app.IsKeyPressed(GLFW_KEY_UP))
	{
		pos.y += speed;
	}
	else if (app.IsKeyPressed(GLFW_KEY_DOWN))
	{
		pos.y -= speed;
	}

	if (app.IsKeyPressed(GLFW_KEY_LEFT))
	{
		pos.x -= speed;
	}
	else if (app.IsKeyPressed(GLFW_KEY_RIGHT))
	{
		pos.x += speed;
	}

	m_Transform->m_Transform.SetPosition(pos);
}