#include "GaPCH.h"
#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float timeStep)
	:	Camera(mat4::Perspective(fov, aspectRatio, -1, 1))
{
}
