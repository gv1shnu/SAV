#pragma once

#include <glad/glad.h> // GLAD before GLFW
#include <GLFW\glfw3.h>

class VertexBuffer
{
public:
		// the constructor creates a buffer
		VertexBuffer(float vertices[], unsigned int count);
		~VertexBuffer();
		// binding vbo 
		void bind() const;

		void unbind() const;
		void setBufferSubData(float vertices[], unsigned int count);
	private:
		// the program ID
		unsigned int ID;
};

