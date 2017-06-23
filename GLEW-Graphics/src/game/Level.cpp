#include "Level.h"
#include "Entity.h"

Level::Level()
{
}

Level::~Level()
{
	RemoveAll();
}

void Level::Add(EntityRef& entity)
{
	entity->OnInit(this);
	m_Entities.push_back(entity);
}

void Level::Remove(const EntityRef& entity)
{
	auto e = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (e != m_Entities.end())
		m_Entities.erase(e);
}

void Level::RemoveAll()
{
	m_Entities.clear();
}

void Level::OnInit()
{
}

void Level::OnUpdate()
{
	for (EntityRef& entity : m_Entities)
		entity->OnUpdate();
}

void Level::OnRender()
{
}
