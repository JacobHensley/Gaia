#pragma once
#include "graphics/layers/Layer.h"
#include "game/Level.h"

class GameLayer : public Layer {
public:	
	GameLayer(const String& name);
	void Init();

	void OnUpdate() override;
	void OnRender() override;
private:
	LevelRef m_Level;
public:
	inline LevelRef GetLevel() { return m_Level; }
};