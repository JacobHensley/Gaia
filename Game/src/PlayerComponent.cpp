#include "PlayerComponent.h"
#include "game/Level.h"
#include "GLFW/glfw3.h"


void PlayerComponent::OnCreate()
{
	m_Transform = GetComponent<TransformComponent>();
	m_Sprite = GetComponent<SpriteComponent>();
}

void PlayerComponent::OnUpdate(float timeStep)
{
	float speed = 5 * timeStep;
	std::cout << speed << std::endl;
}