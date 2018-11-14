#pragma once
#include "math/vec2.h"

struct GLFWwindow;

class Window
{
private:
	friend class Application;

public:
	Window(const char* title, int width, int height);
	~Window();
	
	bool Init();
	void Update();
	void Clear();
	int Closed();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	inline GLFWwindow* GetWindow() { return m_Window; }
private:
	GLFWwindow* m_Window;

	int m_Width, m_Height;
	const char* m_Title;
	bool m_Keys[1024];
	vec2 m_MousePos;
	int m_Button = -1;

	friend void WindowResize(GLFWwindow* window, int width, int height);
	friend void MouseMovementCallback(GLFWwindow* window, double xpos, double ypos);
	friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};