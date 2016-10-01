#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

int main() {

	if (!glfwInit())
		std::cout << "Could not initialize GLFW!" << std::endl;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glClearColor(0.2f, 0.3f, 0.8f, 1.0);

	if (glewInit() != GLEW_OK)
		std::cout << "Could not initialize GLEW!" << std::endl;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}