#include <iostream>
#include "layers/GameLayer.h"
#include "layers/UILayer.h"
#include "graphics/layers/IamGUILayer.h"
#include "Application.h"
#include "game/Level.h"
#include "graphics/Model.h"

int main()
{
	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.PushLayer(new UILayer("UILayer"));
	app.Run();
}