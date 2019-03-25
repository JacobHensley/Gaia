#pragma once
#include "GaPCH.h"
#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float timeStep);
private:

};