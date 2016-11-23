#include "Window.h"
#include <iostream>

Window::Window(const char* title, int width, int height)
	: m_title(title), m_width(width), m_height(height) {
	memset(m_Keys, 0, sizeof(m_Keys));

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

	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, windowResize);
	glfwSetKeyCallback(m_window, KeyCallback);

	if (glewInit() != GLEW_OK) {
		std::cout << "Could not initialize GLEW!" << std::endl;
		return false;
	}	

	glfwSwapInterval(0);

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

void windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_width = width;
	win->m_height = height;
}

void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Keys[key] = action != GLFW_RELEASE;

}
