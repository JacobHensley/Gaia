#include "GaPCH.h"
#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

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
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
	glfwSetCursorPosCallback(m_Window, MouseMovementCallback);

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Could not initialize GLEW!" << std::endl;
		return false;
	}	

	glfwSwapInterval(0);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Window::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::Clear() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void MouseMovementCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	glfwGetCursorPos(window, &xpos, &ypos);
	win->m_MousePos.x = (float)xpos;
	win->m_MousePos.y = (float)ypos;

	ImGuiIO& io = ImGui::GetIO();
	io.MousePos.x = (float)xpos;
	io.MousePos.y = (float)ypos;

}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	ImGuiIO& io = ImGui::GetIO();
	if (action == GLFW_PRESS && button >= 0 && button < 3) 
	{
		win->m_Button = button;
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			io.MouseDown[0] = true;
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			io.MouseDown[1] = true;
	}
		
	if (action == GLFW_RELEASE && button >= 0 && button < 3) 
	{
		win->m_Button = -1;
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			io.MouseDown[0] = false;
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			io.MouseDown[1] = false;
	}
		

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
