#include "Window.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"

Window::Window(const char* title, int width, int height)
	: m_Title(title), m_Width(width), m_Height(height) 
{
	memset(m_Keys, 0, sizeof(m_Keys));

	Init();
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Init()
{
	if (!glfwInit()) 
	{
		std::cout << "Could not initialize GLFW!" << std::endl;
		return false;
	}
		
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

	if (!m_Window) 
	{
		std::cout << "Could not initialize GLFW Window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, WindowResize);
	glfwSetKeyCallback(m_Window, KeyCallback);

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Could not initialize GLEW!" << std::endl;
		return false;
	}	

	glfwSwapInterval(0);

	return true;
}

void Window::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::Clear() 
{
	glClear(GL_COLOR_BUFFER_BIT);
}

int Window::Closed()
{
	return glfwWindowShouldClose(m_Window);
}

void WindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Width = width;
	win->m_Height = height;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Keys[key] = action != GLFW_RELEASE;

	ImGuiIO& io = ImGui::GetIO();
	if (action == GLFW_PRESS)
		io.KeysDown[key] = true;
	if (action == GLFW_RELEASE)
		io.KeysDown[key] = false;
	
	//ImGUI Callback
	(void)mods; // Modifiers are not reliable across systems
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
}
