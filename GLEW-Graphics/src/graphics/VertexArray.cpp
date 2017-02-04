#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_ArrayID));
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_Buffers.size(); i++)
		delete m_Buffers[i];

	GLCall(glDeleteVertexArrays(1, &m_ArrayID))
}


void VertexArray::AddBuffer(Buffer* buffer, uint index)
{
	m_Buffers.push_back(buffer);

	Bind();
	buffer->Bind();

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), 0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(3 * sizeof(float))));

	buffer->Unbind();
	Unbind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_ArrayID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
