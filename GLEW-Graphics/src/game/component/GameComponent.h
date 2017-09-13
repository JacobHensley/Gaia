#pragma once

#include "Component.h"

class GameComponent : public Component
{
private:
public:
	GameComponent() {}
	~GameComponent() {}

	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnUpdate() {}

	static Component::Type* GetStaticType()
	{
		static Component::Type type = { "Game" };
		return &type;
	}

	inline virtual const Component::Type* GetType() const override { return GetStaticType(); }
};