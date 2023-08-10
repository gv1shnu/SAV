#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/glm.hpp"

class Shader
{
	public:
		// constructor reads and builds the shader
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		// Reads shader code
		std::string readShader(const char* shaderPath);
		// Creates shader
		int createShader(const char* source, unsigned int type);
		// Compiles shader
		int compileShader(unsigned int& shaderID);
		// use/activate the shader
		void use() const;
		// creating shader program
		int createProgram(unsigned int& vShaderID, unsigned int& fShaderID);

		// utility uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		// the program ID
		unsigned int ID;
};

#endif