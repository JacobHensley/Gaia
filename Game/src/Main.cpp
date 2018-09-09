#include <iostream>
#include "layers/GameLayer.h"
#include "layers/UILayer.h"
#include "graphics/layers/IamGUILayer.h"
#include "Application.h"
#include "game/Level.h"

int main()
{
	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.PushLayer(new UILayer("UILayer"));
	app.Run();
	
	//

	// type, name, size, offset, length
	// int u_MyInt  4      0       1
	// int u_MyInts 16     4      [4]  
}