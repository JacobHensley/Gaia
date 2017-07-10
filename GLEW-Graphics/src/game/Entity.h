#pragma once
#include "RefCounted.h"
#include "component/Component.h"

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
	virtual void OnUpdate();
};

typedef Ref<Entity> EntityRef;