#include "GaPCH.h"
#include "LayerStack.h"

LayerStack::LayerStack()
{
}


LayerStack::~LayerStack()
{
}

void LayerStack::PushLayer(Layer* layer)
{
	m_LayerStack.push_back(layer);
}

void LayerStack::PushOverlay(Layer* layer)
{
	m_OverlayStack.push_back(layer);
}

void LayerStack::OnRender()
{
	for (uint i = 0; i < m_LayerStack.size(); i++)
	{
		if (m_LayerStack[i]->m_IsActive)
			m_LayerStack[i]->OnRender();
	}

	for (Layer* layer : m_OverlayStack) {
		if (layer->m_IsActive)
			layer->OnRender();
	}
}

void LayerStack::OnUpdate(TimeStep timeStep)
{
	for (Layer* layer : m_LayerStack) {
		layer->OnUpdate(timeStep);
	}

	for (Layer* layer : m_OverlayStack) {
		layer->OnUpdate(timeStep);
	}
}

Layer* LayerStack::GetLayer(const String& name) const
{
	for (uint i = 0; i < m_LayerStack.size(); i++)
	{
		if (m_LayerStack[i]->GetName() == name)
			return m_LayerStack[i];
	}
	return nullptr;
}

Layer* LayerStack::GetOverlay(const String& name) const
{
	for (uint i = 0; i < m_OverlayStack.size(); i++)
	{
		if (m_OverlayStack[i]->GetName() == name)
			return m_OverlayStack[i];
	}
	return nullptr;
}
