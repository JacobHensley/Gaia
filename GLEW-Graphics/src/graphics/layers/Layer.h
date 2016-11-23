#pragma once
#include "../Renderer2D.h"
#include "../../Common.h"

class Layer {
protected: 
	String m_Name;
	Renderer2D* m_Renderer;
	int m_Width, m_Height;
	Camera* m_Camera;
public:
	Layer(const String& name);
	void OnInit();

	virtual void OnUpdate();
	virtual void OnRender();
};