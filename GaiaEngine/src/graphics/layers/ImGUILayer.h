#pragma once
#include "utils/Common.h"
#include "utils/TimeStep.h"
#include "Layer.h"
#include "Application.h"

class GAIA_API ImGUILayer : public Layer {
public:
	ImGUILayer(const String& name);
	~ImGUILayer();
	void OnInit();

	void OnUpdate(TimeStep timeStep) override;
	void OnRender() override;

private:
	void ShowLayerMenu(Application& app, LayerStack* layerStack);
	void ShowUniformMenu(Application& app, LayerStack* layerStack);

};