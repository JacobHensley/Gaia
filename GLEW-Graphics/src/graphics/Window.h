#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();
	
	bool init();
	void update();
	void clear();
	int closed();
private:
	GLFWwindow* m_window;

	int m_width, m_height;
	const char* m_title;
};