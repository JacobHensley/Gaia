#include "Window.h"
#include <iostream>

Window::Window(const char* title, int width, int height)
	: m_title(title), m_width(width), m_height(height) {
	init();
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit()) {
		std::cout << "Could not initialize GLFW!" << std::endl;
		return false;
	}
		
	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

	if (!m_window) {
		std::cout << "Could not initialize GLFW Window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	if (glewInit() != GLEW_OK) {
		std::cout << "Could not initialize GLEW!" << std::endl;
		return false;
	}	

	return true;
}

void Window::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

int Window::closed()
{
	return glfwWindowShouldClose(m_window);
}