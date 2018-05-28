#include "Entity.h"
#include "Level.h"


Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::AddComponent(Component* component)
{
	ASSERT(m_Level, "Temp");

	component->SetEntity(this);
	m_Level->AddComponent(component);
}

void Entity::OnInit(Level* level)
{
	m_Level = level;
}

void Entity::OnUpdate(TimeStep timeStep)
{
}

LevelRef Entity::GetLevel() const
{
	return m_Level;
}