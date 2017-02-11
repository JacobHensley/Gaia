#pragma once
#include "Layer.h"
#include "../Rectangle.h"

class GameLayer : public Layer {
public:	
	GameLayer(const String& name);
	void OnUpdate() override;
	void OnRender() override;
private:
	Texture* texture;
	Rectangle* m_Rectangle;

	float m_Zoom;
};