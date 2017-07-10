#pragma once

#include "Component.h"
#include "graphics/Sprite.h"

class SpriteComponent : public Component
{
public:
	Sprite m_Sprite;
public:
	SpriteComponent(const Sprite& sprite);

	static Component::Type* GetStaticType()
	{
		static Component::Type type = { "Sprite" };
		return &type;
	}

	inline virtual const Component::Type* GetType() const override { return GetStaticType(); }
};