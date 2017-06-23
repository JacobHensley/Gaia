#pragma once

#include <vector>
#include "RefCounted.h"

class Entity;
typedef Ref<Entity> EntityRef;

class Level : public RefCounted
{
protected:
	std::vector<EntityRef> m_Entities;
public:
	Level();
	virtual ~Level();

	void Add(EntityRef& entity);
	void Remove(const EntityRef& entity);
	void RemoveAll();

	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
};

typedef Ref<Level> LevelRef;
