#include "Level.h"
#include "Entity.h"
#include "component/Component.h"
#include "component/SpriteComponent.h"

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
	m_Components[component->GetType()].push_back(component);
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

//	std::cout << "Components:" << std::endl;
	for (auto kv : m_Components) 
	{
	//	std::cout << kv.first->Name << " (" << kv.second.size() << ")" << std::endl;
	}
}

void Level::OnRender()
{
	for (auto kv : m_Components) 
	{
		if (kv.first == SpriteComponent::GetStaticType()) 
			for (auto component : kv.second)
			{
				std::cout << "Name: " << component->GetType()->Name << ", Size: " << kv.second.size() << std::endl;
				
			}
	}
}

void Level::OnRender(Renderer2D* renderer2D)
{
	for (auto kv : m_Components)
	{
		if (kv.first == SpriteComponent::GetStaticType())
			for (auto component : kv.second)
			{
				std::cout << "Name: " << component->GetType()->Name << ", Size: " << kv.second.size() << std::endl;
				renderer2D->Begin();

				SpriteComponent* comp = (SpriteComponent*)component;

				renderer2D->Submit(&comp->m_Sprite, 0.5f, 0.5f, 10, 10);

				renderer2D->End();
				renderer2D->Flush();
			}
	}
}
