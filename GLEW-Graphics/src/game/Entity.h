#pragma once

class Level;

class Entity
{
protected:
	Level* m_Level;
public:
	Entity();
	virtual ~Entity();

	virtual void OnInit(Level* level);
	virtual void OnUpdate();
};