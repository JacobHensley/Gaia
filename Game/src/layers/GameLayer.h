#pragma once
#include "graphics/layers/Layer.h"
#include "graphics/Model.h"
#include "game/Level.h"

class GameLayer : public Layer {
public:	
	GameLayer(const String& name);
	void OnInit();

	void OnUpdate(TimeStep timeStep) override;
	void OnRender() override;
private:
	LevelRef m_Level;
	Model* m_BunnyModel;
	Shader* m_BunnyShader;
public:
	inline LevelRef GetLevel() { return m_Level; }
};