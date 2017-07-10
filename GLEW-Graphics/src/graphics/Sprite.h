#pragma once

#include "RefCounted.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Sprite : RefCounted 
{
private:
	friend class Renderer2D;
private:
	static VertexBufferRef m_VertexBuffer;
	static IndexBufferRef m_IndexBuffer;
	static Shader* m_Shader;
public:
	Sprite();
	Sprite(vec4 color);

	vec4 m_Color;
private:
	void Init();
};