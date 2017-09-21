#include "PlayerComponent.h"
#include "game/Level.h"

void PlayerComponent::OnCreate()
{
	std::cout << "Created Player" << std::endl;
	m_Transform = GetComponent<TransformComponent>();
	m_Sprite = GetComponent<SpriteComponent>();
}

void PlayerComponent::OnUpdate()
{
	std::cout << "updated Player" << std::endl;
}