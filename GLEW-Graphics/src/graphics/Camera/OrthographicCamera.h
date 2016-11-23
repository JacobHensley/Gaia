#pragma once

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float left, float right, float top, float bottom);
	void OnUpdate() override;

};