#include <iostream>
#include "graphics/Window.h"

#include "Application.h"
#include "graphics/layers/GameLayer.h"
#include "RefCounted.h"

class TestRect : public RefCounted 
{
private:
	int x, y;
public:
	TestRect(int x, int y) : x(x), y(y) {}
	~TestRect()
	{
		std::cout << "obj Entity Got Deleted" << std::endl;
	}

	void Print() const 
	{
		std::cout << "X: " << x << ", Y: " << y << std::endl;
	}

};

typedef Ref<TestRect> RectRef;

void Print(const RectRef& entity)
{
	entity->Print();
}

class TestLayer
{
private:
	RectRef entity;
public:
	TestLayer() 
	{
		entity = new TestRect(5, 6);
	}

	void update()
	{
		Print(entity);
	}
};

void TestRefCounting() 
{
	TestLayer layer = TestLayer();
	layer.update();

	std::cout << "Hello" << std::endl;
}

int main() {

//	TestRefCounting();
//	system("PAUSE");
//	return 0;

	Application app("Test Window", 1280, 720);

	app.PushLayer(new GameLayer("GameLayer"));
	app.Run();

	//TODO:
	//ref counting
	//Materials
	//setup buffer layouts
	//Memory Arena
	//Font Rendering
	//add static asserts, etc
	//Debug Layer Labels
	//String Formatting

	return 0;
}