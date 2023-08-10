#pragma once

#include <glad/glad.h> // GLAD before GLFW
#include <GLFW\glfw3.h>

class VertexBuffer
{
public:
		VertexBuffer();
		// the constructor creates a buffer
		VertexBuffer(float vertices[], size_t size);
		~VertexBuffer();
		// binding vbo 
		void bind() const;

		void unbind() const;
		void setData(float vertices[], size_t size);
	private:
		// the program ID
		unsigned int ID;
};

