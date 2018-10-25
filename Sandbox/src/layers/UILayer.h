#pragma once
#include "graphics/layers/Layer.h"


class UILayer : public Layer
{
public:
	UILayer(const String& name);
	void OnInit();

	void OnUpdate(TimeStep timeStep) override;
	void OnRender() override;
};

