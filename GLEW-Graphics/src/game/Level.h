#pragma once

#include <vector>

class Entity;

class Level
{
protected:
	std::vector<Entity*> m_Entities;
public:
	Level();
	virtual ~Level();

	void Add(Entity* entity);
	void Remove(Entity* entity);
	void RemoveAll();

	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
};
