#include "Camera.h"


Camera::Camera(const mat4& projection)
	:	m_Proj(projection), m_View(mat4::Identity())	
{
}


Camera::~Camera()
{
}

void Camera::OnUpdate(float timeStep)
{
	
}
