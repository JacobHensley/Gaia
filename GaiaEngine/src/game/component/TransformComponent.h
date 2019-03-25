#pragma once
#include "Component.h"
#include "math/mat4.h"

class GAIA_API TransformComponent : public Component
{
public:
	mat4 m_Transform;

public:
	TransformComponent(const mat4& transform);

	static Component::Type* GetStaticType()
	{
		static Component::Type type = { "Transform" };
		return &type;
	}

	inline virtual Component::Type* GetType() const override { return GetStaticType(); }

};