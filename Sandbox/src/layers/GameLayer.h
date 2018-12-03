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
	float m_Scale = 00.2f;
	vec3 m_Angle{0, 0, 0};
	vec3 m_LightPos{ 5, 5, 5 };
	vec3 m_LightColor{ 1, 1, 1 };
	vec3 m_ObjectColor{ 0.7f, 0.7f, 0.7f };
public:
	inline LevelRef GetLevel() { return m_Level; }
};