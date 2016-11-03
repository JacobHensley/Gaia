#pragma once
#include "../Renderer2D.h"
#include "../../Common.h"

class Layer {
protected: 
	String m_Name;
	Renderer2D* m_Renderer;
public:
	Layer(const String& name);
	void OnInit();

	virtual void OnUpdate();
	virtual void OnRender();
};