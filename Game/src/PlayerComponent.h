#pragma once


#include "game/component/GameComponent.h"

class PlayerComponent : public GameComponent
{
private:

public:
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
};