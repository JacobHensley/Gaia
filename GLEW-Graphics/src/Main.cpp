#include <iostream>
#include "graphics\Window.h"

#include "Common.h"
#include "graphics\VertexArray.h"
#include "graphics\IndexBuffer.h"
#include "graphics\Buffer.h"
#include "graphics\Shader.h"
#include "graphics\Texture.h"

int main() {

	Window window = Window("Test Window", 1280, 720);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f
	};

	uint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mat4 matrix = mat4::Translate(vec3(0.0f, 0.0f, 0.0f));

	VertexArray vertexArray;
	IndexBuffer ibo = IndexBuffer(indices, 6);
	vertexArray.addBuffer(new Buffer(vertices, 4 * 5, 3), 0);

	vertexArray.bind();
	ibo.bind();

	Texture text = Texture("res/jungle.png");

	Shader shader("Shaders/shader.vert", "Shaders/shader.frag");
	shader.bind();

	shader.SetUniform1i("u_Texture", 0);

	shader.SetUniformMat4("u_ModelMatrix", matrix);
//	shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	while (!window.closed()) {
		window.clear();

		ibo.draw();

		window.update();
	}

	return 0;
}