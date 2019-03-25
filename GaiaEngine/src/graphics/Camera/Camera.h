#pragma once
#include "GaPCH.h"
#include "math/mat4.h"
#include "utils/RefCounted.h"
#include "utils/TimeStep.h"

class Camera : public  RefCounted
{
protected:
	mat4 m_Proj, m_View;
	vec3 m_Position, m_Rotation, m_FocalPoint;
public:
	Camera(const mat4& projection);
	~Camera();

	inline const mat4& GetProjectionMatrix() const { return m_Proj; }
	inline const mat4& GetViewMatrix() const { return m_View; }

	inline void SetProjectionMatrix(const mat4& projectionMatrix) { m_Proj = projectionMatrix; }
	inline void SetViewMatrix(const mat4& ViewMatrix) { m_View = ViewMatrix; }

	virtual void OnUpdate(TimeStep timeStep);

	virtual void OnFocus() { }

	inline const vec3& GetPosition() const { return m_Position; }
	inline void SetPosition(const vec3& position) { m_Position = position; }

	inline const vec3& GetRotation() const { return m_Rotation; }
	inline void SetRotation(const vec3& rotation) { m_Rotation = rotation; }

	inline void Translate(const vec3& translation) { m_Position += translation; }
	inline void Rotate(const vec3& rotation) { m_Rotation += rotation; }

	inline void Translate(float x, float y, float z) { m_Position += vec3(x, y, z); }
	inline void Rotate(float x, float y, float z) { m_Rotation += vec3(x, y, z); }

	inline const vec3& GetFocalPoint() const { return m_FocalPoint; }

	inline const mat4& GetViewMatrix() { return m_View; }
};

typedef Ref<Camera> CameraRef;

