#pragma once
#include "GaPCH.h"
#include "Component.h"
#include "math/mat4.h"

class TransformComponent : public Component
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