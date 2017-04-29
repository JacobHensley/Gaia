#include "Level.h"

#include "Entity.h"

Level::Level()
{
}

Level::~Level()
{
	RemoveAll();
}

void Level::Add(Entity* entity)
{
	entity->OnInit(this);
	m_Entities.push_back(entity);
}

void Level::Remove(Entity* entity)
{
	auto e = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (e != m_Entities.end())
	{
		delete *e;
		m_Entities.erase(e);
	}
}

void Level::RemoveAll()
{
	for (Entity* entity : m_Entities)
		delete entity;
	m_Entities.clear();
}

void Level::OnInit()
{
}

void Level::OnUpdate()
{
	for (Entity* entity : m_Entities)
		entity->OnUpdate();
}

void Level::OnRender()
{
}
