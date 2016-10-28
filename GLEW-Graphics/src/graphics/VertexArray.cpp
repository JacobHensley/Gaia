#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_arrayID));
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

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), 0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(3 * sizeof(float))));

	buffer->unbind();
	unbind();
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_arrayID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
