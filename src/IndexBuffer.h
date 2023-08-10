#pragma once

#include <glad/glad.h> // GLAD before GLFW
#include <GLFW\glfw3.h>

class IndexBuffer
{
	public:
		// the constructor creates a buffer
		IndexBuffer(unsigned int indices[], size_t count);
		~IndexBuffer();
		// binding the buffer to element array
		void bind() const;
		void unbind() const;
	private:
		unsigned int ID;

};

