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
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(3 * sizeof(float)));

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
