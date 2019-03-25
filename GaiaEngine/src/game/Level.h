#pragma once
#include "GaPCH.h"
#include "utils/RefCounted.h"
#include "graphics/Renderer2D.h"
#include "component/ComponentCahe.h"
#include "utils/TimeStep.h"

class Entity;
typedef Ref<Entity> EntityRef;

class Level : public RefCounted
{
protected:
	std::vector<EntityRef> m_Entities;
	ComponentCache m_ComponentCache;
public:
	Level();
	virtual ~Level();

	void Add(EntityRef& entity);
	void AddComponent(Component* component);
	void Remove(const EntityRef& entity);
	void RemoveAll();

	template<typename T>
	Ref<T> CreateEntity() 
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must inherit from Entity");
		Ref<T> entity = new T();
		Add(entity);

		return entity;
	}

	template<typename T>
	T* GetComponent(const Entity* entity)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		return m_ComponentCache.Get<T>(entity);
	}

	virtual void OnInit();
	virtual void OnUpdate(TimeStep timeStep);
	virtual void OnRender(Renderer2D* renderer2D);
};

template<typename T>
T* Entity::GetComponent() {
	return m_Level->GetComponent<T>(this);
}

typedef Ref<Level> LevelRef;
