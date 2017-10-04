#pragma once
#include "RefCounted.h"
#include "component/Component.h"
#include "TimeStep.h"

class Component;
typedef Ref<Component> ComponentRef;

class Level;
typedef Ref<Level> LevelRef;

class Entity : public RefCounted
{
protected:
	LevelRef m_Level;
public:
	Entity();
	virtual ~Entity();

	void AddComponent(Component* component);

	virtual void OnInit(Level* level);
	virtual void OnUpdate(TimeStep timeStep);

	template<typename T>
	T* GetComponent();

	LevelRef GetLevel() const;
};

typedef Ref<Entity> EntityRef;