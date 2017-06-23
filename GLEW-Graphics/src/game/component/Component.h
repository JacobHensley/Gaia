#pragma once
#include "Common.h"
#include "game/Entity.h"

class Component
{
public:
	struct Type
	{
		String Name;
	};
public:

	inline Entity* GetEntity() { return m_Entity; }
	inline const Entity* GetEntity() const { return m_Entity; }

	virtual const Type* GetType() const { return nullptr; }

protected:
	Entity* m_Entity;
};