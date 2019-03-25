#pragma once
#include "GaPCH.h"
#include "graphics/Camera/Camera.h"
#include "math/Quaternion.h"

class MayaCamera : public Camera
{
private:
	bool m_Panning, m_Rotating;
	vec2 m_InitialMousePosition;
	vec3 m_InitialFocalPoint, m_InitialRotation;

	float m_Distance;
	float m_PanSpeed, m_RotationSpeed, m_ZoomSpeed;

	float m_Pitch, m_Yaw;
public:
	MayaCamera(const mat4& projectionMatrix);
	void OnFocus() override;
	void OnUpdate(TimeStep timeStep) override;

	inline float GetDistance() const { return m_Distance; }
	inline void SetDistance(float distance) { m_Distance = distance; }
private:
	void MousePan(const vec2& delta);
	void MouseRotate(const vec2& delta);
	void MouseZoom(float delta);

	// TODO: Move up to camera class
	vec3 GetUpDirection();
	vec3 GetRightDirection();
	vec3 GetForwardDirection();

	vec3 CalculatePosition();
	Quaternion GetOrientation();
};