#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_arrayID);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_buffers.size(); i++)
		delete m_buffers[i];
}


void VertexArray::addBuffer(Buffer* buffer, uint index)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	buffer->unbind();
	unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_arrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
