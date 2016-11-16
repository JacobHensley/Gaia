#include "Camera.h"
#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
	:	Camera(mat4::Orthographic(left, right, top, bottom, -1, 1))	{
}
