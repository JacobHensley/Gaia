#pragma once
#include "Layer.h"

class UILayer : public Layer
{
public:
	UILayer(const String& name);

	void OnUpdate(TimeStep timeStep) override;
	void OnRender() override;
};

