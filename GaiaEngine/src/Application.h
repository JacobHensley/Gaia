#pragma once
#include "GaPCH.h"
#include "graphics/Window.h"
#include "utils/Common.h"
#include "graphics/layers/Layer.h"
#include "graphics/layers/LayerStack.h"

class Application
{
private:
	static Application* s_Application;
private:
	Window* m_Window;

	LayerStack* m_LayerStack;
	TimeStep m_TimeStep;

	double m_LastTime;
	int m_NbFrames;

	double m_MSFrame;
	double m_FPS;
public:
	Application(const String& name, int width, int height);
	~Application();	

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	void OnRender();
	void OnUpdate(TimeStep timesStep);

	void Run();

	inline int GetWidth() const { return m_Window->GetWidth(); }
	inline int GetHeight() const { return m_Window->GetHeight(); }

	inline LayerStack* GetLayerStack() const { return m_LayerStack; }

	inline double GetMSFrame() const { return m_MSFrame; }
	inline double GetFPS() const { return m_FPS; }

	inline bool IsKeyPressed(int keycode) const { ASSERT(keycode >= 0 && keycode < 1024); return m_Window->m_Keys[keycode]; }
	inline int GetMouseButton() const { return m_Window->m_Button; }
	inline vec2 GetMousePos() const { return m_Window->m_MousePos; }
	inline Window* GetWindow() const { return m_Window; }

	void Shutdown();
public:
	static inline Application& GetApplication() { return *s_Application; };
};