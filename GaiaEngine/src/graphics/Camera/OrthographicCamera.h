#pragma once

class GAIA_API OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float left, float right, float top, float bottom);
	void OnUpdate(TimeStep timeStep) override;

};