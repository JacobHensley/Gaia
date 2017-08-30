#include <iostream>

#include "Application.h"
#include "GameLayer.h"
#include "TestLayer.h"
#include "game/Level.h"

int main()
{
	Application app("Test Window", 1280, 720);

//	app.PushLayer(new TestLayer("TestLayer"));

	app.PushLayer(new GameLayer("GameLayer"));
	app.Run();

	//HW:
	//1: Finish SpriteComponent by adding Sprite to it - Done
	//2: Give a entity a SpriteComponent - Done
	//3: Iterate through m_Components in Level::OnRender() - Done
	//4: Render SpriteComponents - Done
	//5 (Extra): Fix bug when deleting IndexBuffer
	//6 (Bonus): Find the entities TransformComponent and use that to render the SpriteComponent

	//Next class talk about cleaning up the Engine

	//TODO:
	//Game
	//Entity System
	//Materials
	//Memory Arena
	//Font Rendering
	//add static asserts, etc
	//Debug Layer Labels
	//String Formatting
	//sprites

	return 0;
}