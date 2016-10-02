#include <iostream>
#include "graphics\Window.h"
#include "utils\FileUtils.h"

int main() {

	Window window = Window("Test Window", 720, 1280);

	while (!window.closed()) {
		window.clear();
		window.update();
	}

	return 0;
}