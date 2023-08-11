#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::bind() const
{
	glBindVertexArray(ID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;

	// set the vertex attributes pointers
	for (unsigned int i=0;i<elements.size();i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, 
			element.normalised, layout.getStride(),
			(const void*)(intptr_t)offset);
		offset += element.count * sizeof(element.type);
	}
}

