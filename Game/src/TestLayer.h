#pragma once
#include "graphics/layers/Layer.h"
#include "graphics/Rectangle.h"

class TestLayer : public Layer {
public:	

	TestLayer(const String& name);
	void OnUpdate() override;
	void OnRender() override;
private:
	Texture* texture;
	Renderable2DRef m_Rectangle;

	float m_Zoom;
};