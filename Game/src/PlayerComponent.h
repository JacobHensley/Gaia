#pragma once

#include "game/component/GameComponent.h"
#include "game/component/TransformComponent.h"
#include "game/component/SpriteComponent.h"

class PlayerComponent : public GameComponent
{
private:
	TransformComponent* m_Transform;
	SpriteComponent* m_Sprite;
public:
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
};