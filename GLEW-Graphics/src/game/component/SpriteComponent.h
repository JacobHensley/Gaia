#pragma once

#include "Component.h"

class SpriteComponent : public Component
{
public:
	mat4 Transform;

public:
	TransformComponent(const mat4& transform);

	static Component::Type* GetStaticType()
	{
		static Component::Type type = { "Sprite" };
		return &type;
	}

	inline virtual const Component::Type* GetType() const override { return GetStaticType(); }

};