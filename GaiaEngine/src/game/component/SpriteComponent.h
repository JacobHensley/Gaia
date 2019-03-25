#pragma once
#include "GaPCH.h"
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

	inline virtual Component::Type* GetType() const override { return GetStaticType(); }
};