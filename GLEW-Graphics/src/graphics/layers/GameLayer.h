#pragma once
#include "Layer.h"

class GameLayer : public Layer {
public:	
	GameLayer(const String& name);
	void OnRender();
};