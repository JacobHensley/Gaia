#include "Camera.h"


Camera::Camera(const mat4& projection)
	:	m_Proj(projection), m_View(mat4::Identity())	
{
	m_Position = vec3();
	m_Rotation = vec3();
}


Camera::~Camera()
{
}

void Camera::OnUpdate(TimeStep timeStep)
{
	
}
