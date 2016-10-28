#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(uint* data, GLsizei count)
	:	m_count(count)	{
	GLCall(glGenBuffers(1, &m_bufferID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::draw() const
{	
	GLCall(glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, NULL));
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
