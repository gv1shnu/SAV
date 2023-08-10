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
		inline unsigned int getCount() const { return m_Count; }
	private:
		unsigned int ID;
		unsigned int m_Count;
};

