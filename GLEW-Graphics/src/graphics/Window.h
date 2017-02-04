#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

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
private:
	GLFWwindow* m_Window;

	int m_Width, m_Height;
	const char* m_Title;
	bool m_Keys[1024];
	friend void windowResize(GLFWwindow* window, int width, int height);
	friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};