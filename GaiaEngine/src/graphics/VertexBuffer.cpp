#include "GaPCH.h"
#include "VertexBuffer.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(uint count)
{
	GLCall(glGenBuffers(1, &m_BufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), NULL, GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::VertexBuffer(float* data, int count)
{
	GLCall(glGenBuffers(1, &m_BufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_BufferID))
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));


}
 
void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Unmap()
{
	GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
}

void * VertexBuffer::MapInternal()
{
	GLCall(void* result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	return result;
}
