#pragma once
#include "GaPCH.h"
#include "Component.h"

class GameComponent : public Component
{
private:
public:
	GameComponent() {}
	~GameComponent() {}

	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnUpdate(TimeStep timeStep) {}

	static Component::Type* GetStaticType()
	{
		static Component::Type type = { "Game" };
		return &type;
	}

	inline virtual Component::Type* GetType() const override { return GetStaticType(); }
};