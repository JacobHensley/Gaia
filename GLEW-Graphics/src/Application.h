#pragma once
#include "graphics\Window.h"
#include "Common.h"
#include <vector>
#include "graphics\layers\Layer.h"

class Application
{
private:
	static Application* s_Application;
private:
	Window* m_Window;
	std::vector<Layer*> m_LayerStack;
public:
	Application(const String& name, int width, int height);
	~Application();	

	void PushLayer(Layer* layer);
	void OnRender();
	void Run();
	inline int GetWidth() const { return m_Window->GetWidth(); }
	inline int GetHeight() const { return m_Window->GetHeight(); }

public:
	static inline Application& GetApplication() { return *s_Application; };
};