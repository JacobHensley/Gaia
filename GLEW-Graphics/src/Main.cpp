#include <iostream>
#include "graphics\Window.h"

#include "Application.h"
#include "graphics\layers\GameLayer.h"

int main() {

	//onInit in push layer - on hold
	//Might be Error in perspectiveCam

	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.Run();

	return 0;
}