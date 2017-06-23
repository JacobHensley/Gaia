#include "Entity.h"
#include "Level.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::OnInit(Level* level)
{
	m_Level = level;
}

void Entity::OnUpdate()
{
}
