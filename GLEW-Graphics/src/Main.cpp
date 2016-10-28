#include <iostream>
#include "graphics\Window.h"

#include "Common.h"
#include "graphics\VertexArray.h"
#include "graphics\IndexBuffer.h"
#include "graphics\Buffer.h"
#include "graphics\Shader.h"
#include "graphics\Texture.h"

#include "graphics\Rectangle.h"
#include "graphics\Renderer2D.h"

int main() {

	Window window = Window("Test Window", 1280, 720);

	Rectangle rectangle(0, 0, 2, 2);
	Renderer2D renderer;

	float z = 0;

	while (!window.closed()) {
		window.clear();
		renderer.Begin();
		renderer.Submit(&rectangle);
		renderer.End();
		renderer.Flush();

		z -= 0.01f;
		rectangle.SetTransform(mat4::Translate(vec3(0.0f, 0.0f, z)));
		window.update();
	}

	return 0;
}