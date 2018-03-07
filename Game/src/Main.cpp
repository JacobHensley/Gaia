#include <iostream>
#include "Application.h"
#include "GameLayer.h"
#include "game/Level.h"
#include "graphics/layers/UILayer.h"

int main()
{
	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.PushLayer(new UILayer("UILayer"));
	app.Run();
}