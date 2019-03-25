#pragma once
#include "graphics/Renderer2D.h"
#include "utils/Common.h"
#include "utils/TimeStep.h"

class GAIA_API Layer
{
protected: 
	String m_Name;
	Renderer2D* m_Renderer;
	int m_Width, m_Height;
	CameraRef m_Camera;
	
public:
	Layer(const String& name);
	void OnInit();

	inline const String& GetName() const { return m_Name; }

	virtual void OnUpdate(TimeStep timeStep);
	virtual void OnRender();
public:
	bool m_IsActive = true;
};