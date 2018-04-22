#pragma once
#include "utils/Common.h"
#include "game/Entity.h"
#include "utils/RefCounted.h"

class Entity;

class Component : public RefCounted
{
public:
	struct Type
	{
		String Name;
	};
public:

	virtual Type* GetType() const { return nullptr; }

	inline Entity* GetEntity() { return m_Entity; }
	inline const Entity* GetEntity() const { return m_Entity; }
	inline void SetEntity(Entity* entity) { m_Entity = entity; }

	template<typename T>
	T* GetComponent()
	{
		return m_Entity->GetComponent<T>();
	}

protected:
	Entity* m_Entity;
};

typedef Ref<Component> ComponentRef;