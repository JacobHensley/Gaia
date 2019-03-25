#pragma once
#include "GaPCH.h"
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

	void OnRender();
	void OnUpdate(TimeStep timeStep);

	Layer* GetLayer(const String& name) const;
	Layer* GetOverlay(const String& name) const;

	inline std::vector<Layer*> GetLayers() const { return m_LayerStack; }
	inline std::vector<Layer*> GetOverlays() const { return m_OverlayStack; }
};

