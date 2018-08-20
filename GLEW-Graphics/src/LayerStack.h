#pragma once
#include "graphics/layers/Layer.h"
#include "utils/TimeStep.h"
#include "utils/Common.h"

class LayerStack
{
private:
	std::vector<Layer*> m_LayerStack;
	std::vector<Layer*> m_OverlayStack;
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	void OnRedner();
	void OnUpdate(TimeStep timeStep);

	Layer* GetLayer(String& name) const;
	Layer* GetOverlay(String& name) const;

	inline std::vector<Layer*> GetLayers() const { return m_LayerStack; }
	inline std::vector<Layer*> GetOverlays() const { return m_OverlayStack; }
};

