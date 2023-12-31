#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(float vertices[], unsigned int count)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, count *sizeof(float), vertices, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setBufferSubData(float vertices[], unsigned int count)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, count*sizeof(float), vertices);
}