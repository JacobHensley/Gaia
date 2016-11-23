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

	double lastTime = glfwGetTime();
	int nbFrames = 0;
public:
	Application(const String& name, int width, int height);
	~Application();	

	void PushLayer(Layer* layer);
	void OnRender();
	void OnUpdate();
	void Run();
	inline int GetWidth() const { return m_Window->GetWidth(); }
	inline int GetHeight() const { return m_Window->GetHeight(); }
	inline bool IsKeyPressed(int keycode) const { ASSERT(keycode >= 0 && keycode < 1024); return m_Window->m_Keys[keycode]; }

public:
	static inline Application& GetApplication() { return *s_Application; };
};