#include "GaPCH.h"
#include "VertexArray.h"
#include "GL/glew.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArray);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexArray)
}

void VertexArray::PushVertexBuffer(VertexBuffer* VB)
{
	glBindVertexArray(m_VertexArray);
	VB->Bind();

	const BufferLayout& layout = VB->GetLayout();

	const auto& elements = layout.GetElements();
	uint stride = layout.GetStride();
	for (uint i = 0; i < elements.size(); i++)
	{
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, GL_FALSE, stride, (const void*)elements[i].offset));
	}

	glBindVertexArray(0);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_VertexArray);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
