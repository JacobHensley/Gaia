#include <iostream>

#include "Application.h"
#include "GameLayer.h"
#include "game/Level.h"

#include <ft2build.h>
#include FT_FREETYPE_H

int main()
{

	FT_Library  library;

	int error = FT_Init_FreeType(&library);
	if (error)
	{
		std::cout << "FreeType Error!" << std::endl;
	}

	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.Run();

	//TODO:
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