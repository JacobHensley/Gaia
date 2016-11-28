#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "../math/mat4.h"

class Renderable2D
{
private:
	friend class Renderer2D;
protected:
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;
	Shader* m_Shader;
	Texture* m_Texture;
	mat4 m_Transform;
public:
	Renderable2D();
	virtual ~Renderable2D();

	inline void SetTransform(const mat4& transform) { m_Transform = transform; }
};
