#pragma once
#include "RefCounted.h"

class Level;
typedef Ref<Level> LevelRef;

class Entity : public RefCounted
{
protected:
	LevelRef m_Level;
public:
	Entity();
	virtual ~Entity();

	virtual void OnInit(Level* level);
	virtual void OnUpdate();
};

typedef Ref<Entity> EntityRef;