#include "Buffer.h"

Buffer::Buffer(GLfloat* data, GLsizei count, uint componentCount)
	:	m_componentCount(componentCount)	{

	GLCall(glGenBuffers(1, &m_bufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Buffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
}
 
void Buffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
