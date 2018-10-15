#pragma once
#include "utils/Common.h"
#include "utils/TimeStep.h"
#include "Layer.h"

class IamGUILayer : public Layer {
public:
	IamGUILayer(const String& name);
	~IamGUILayer();
	void OnInit();

	void OnUpdate(TimeStep timeStep) override;
	void OnRender() override;
};