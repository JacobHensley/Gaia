#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "../math/mat4.h"
#include "RefCounted.h"

class Renderable2D : public RefCounted 
{
private:
	friend class Renderer2D;
protected:
	VertexArrayRef m_VertexArray;
	IndexBufferRef m_IndexBuffer;
	Shader* m_Shader;
	TextureRef m_Texture;
	mat4 m_Transform;
public:
	Renderable2D();
	virtual ~Renderable2D();

	inline void SetTransform(const mat4& transform) { m_Transform = transform; }
};

typedef Ref<Renderable2D> Renderable2DRef;