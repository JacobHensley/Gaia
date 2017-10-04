#include <iostream>

#include "Application.h"
#include "GameLayer.h"
#include "game/Level.h"

int main()
{
	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.Run();

	//TODO: Fix bug when deleting IndexBuffer (?)

	//Convert to timeStep Struc

	//TODO:
	//Timestep
	//Game
	//Text
	//Materials
	//Memory Arena
	//Font Rendering
	//add static asserts, etc
	//Debug Layer Labels
	//String Formatting
	//Allocation Tracking

	return 0;
}