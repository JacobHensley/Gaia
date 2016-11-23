#pragma once
#include "Layer.h"

class GameLayer : public Layer {
public:	
	GameLayer(const String& name);
	void OnUpdate() override;
	void OnRender() override;
private:
	float m_zoom;
};