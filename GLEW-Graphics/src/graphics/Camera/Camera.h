#pragma once

#include "math/mat4.h"
#include "utils/RefCounted.h"
#include "utils/TimeStep.h"

class Camera : public  RefCounted
{
protected:
	mat4 m_Proj, m_View;
public:
	Camera(const mat4& projection);
	~Camera();

	inline const mat4& GetProjectionMatrix() const { return m_Proj; }
	inline const mat4& GetViewMatrix() const { return m_View; }

	inline void SetProjectionMatrix(const mat4& projectionMatrix) { m_Proj = projectionMatrix; }
	inline void SetViewMatrix(const mat4& ViewMatrix) { m_View = ViewMatrix; }

	virtual void OnUpdate(TimeStep timeStep);
};

typedef Ref<Camera> CameraRef;

