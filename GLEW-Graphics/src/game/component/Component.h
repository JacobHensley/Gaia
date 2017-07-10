#pragma once
#include "Common.h"
#include "game/Entity.h"
#include "RefCounted.h"

class Entity;

class Component : public RefCounted
{
public:
	struct Type
	{
		String Name;
	};
public:

	inline Entity* GetEntity() { return m_Entity; }
	inline const Entity* GetEntity() const { return m_Entity; }

	inline void SetEntity(Entity* entity) { m_Entity = entity; }

	virtual const Type* GetType() const { return nullptr; }

protected:
	Entity* m_Entity;
};

typedef Ref<Component> ComponentRef;