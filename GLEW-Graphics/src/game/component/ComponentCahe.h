#pragma once
#include <unordered_map>
#include <vector>
#include "Component.h"

class ComponentCache
{
private:
	std::unordered_map<Component::Type*, std::vector<Component*>> m_Components;
	std::unordered_map<Entity*, std::unordered_map<Component::Type*, Component*>> m_EntityComponents;
public:

	template<typename T>
	const std::vector<Component*>& GetAll()
	{
		//TODO: add static assert 
		return m_Components[T::GetStaticType()];
	}

	template<typename T>
    T* Get(const Entity* entity)
	{
		//TODO: add static assert 
		return (T*)m_EntityComponents[(Entity*)entity][T::GetStaticType()];
	}

	void Add(Component* component) 
	{
		m_Components[component->GetType()].push_back(component);
		m_EntityComponents[component->GetEntity()][component->GetType()] = component;
	}

	void ClearAll() 
	{
		m_Components.clear();
		m_EntityComponents.clear();
	}

};