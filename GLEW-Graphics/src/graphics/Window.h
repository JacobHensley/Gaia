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
	
	bool init();
	void update();
	void clear();
	int closed();

	inline int GetWidth() { return m_width; }
	inline int GetHeight() { return m_height; }
private:
	GLFWwindow* m_window;

	int m_width, m_height;
	const char* m_title;
	bool m_Keys[1024];
	friend void windowResize(GLFWwindow* window, int width, int height);
	friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};