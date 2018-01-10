#pragma once
#include "graphics/layers/Layer.h"
#include "Common.h"
#include "game/Level.h"

class DemoLayer : public Layer
{
public:
	DemoLayer(const String& name);
	void Init();

	void OnUpdate(TimeStep timeStep) override;
	void OnRender() override;
private:
	LevelRef m_Level;
public:
};