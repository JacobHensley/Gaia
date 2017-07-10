#pragma once

#include <vector>
#include "RefCounted.h"
#include "component/Component.h"
#include <type_traits>
#include "graphics/Renderer2D.h"

class Entity;
typedef Ref<Entity> EntityRef;

class Level : public RefCounted
{
protected:
	std::vector<EntityRef> m_Entities;
	std::unordered_map<const Component::Type*, std::vector<Component*>> m_Components;
public:
	Level();
	virtual ~Level();

	void Add(EntityRef& entity);
	void AddComponent(Component* component);
	void Remove(const EntityRef& entity);
	void RemoveAll();

	template<typename T>
	Ref<T> CreateEntity() {
		static_assert(std::is_base_of<Entity, T>::value, "T must inherit from Entity");
		Ref<T> entity = new T();
		Add(entity);
		return entity;
	}

	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnRender(Renderer2D* renderer2D);
};

typedef Ref<Level> LevelRef;
