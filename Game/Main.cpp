#include <iostream>

#include "Application.h"
#include "src/GameLayer.h"

int main() {

	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.Run();

	//TODO:
	//Game
	//Entity System
	//Materials
	//Memory Arena
	//Font Rendering
	//add static asserts, etc
	//Debug Layer Labels
	//String Formatting

	return 0;
}