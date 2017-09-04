#include "Level.h"
#include "Entity.h"
#include "component/Component.h"
#include "component/SpriteComponent.h"
#include "component/TransformComponent.h"

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

void Level::AddComponent(Component* component)
{
	m_ComponentCache.Add(component);
}

void Level::Remove(const EntityRef& entity)
{
	auto e = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (e != m_Entities.end())
		m_Entities.erase(e);
}

void Level::RemoveAll()
{
	m_ComponentCache.ClearAll();
}

void Level::OnInit()
{
}

void Level::OnUpdate()
{
	for (EntityRef& entity : m_Entities)
		entity->OnUpdate();

}

void Level::OnRender(Renderer2D* renderer2D)
{
	auto& spriteComponents = m_ComponentCache.GetAll<SpriteComponent>();
	renderer2D->Begin();

	for (auto component : spriteComponents)
	{

		SpriteComponent* comp = (SpriteComponent*)component;
		const TransformComponent*  tc = m_ComponentCache.Get<TransformComponent>(comp->GetEntity());

		renderer2D->Submit(&comp->m_Sprite, tc->m_Transform.GetPosition().x, tc->m_Transform.GetPosition().y, 10, 10);
	}

	renderer2D->End();
	renderer2D->Flush();
}
