#pragma once
#include "Camera.h"

class GAIA_API PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float timeStep);
private:

};