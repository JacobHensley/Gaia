#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio)
	:	Camera(mat4::Perspective(fov, aspectRatio, -1, 1))
{
}
