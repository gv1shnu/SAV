#pragma once

#include <glad/glad.h> // GLAD before GLFW
#include <GLFW\glfw3.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
	public:
		// the constructor creates vertex array
		VertexArray();
		~VertexArray();
		// binding vao 
		void bind() const;
		void unbind() const;
		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	private:
		// the program ID
		unsigned int ID;
};

